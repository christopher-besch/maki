#include "pch.h"

#include "render_driver.h"

namespace Maki {

// all functions to be run from rendering thread
void RenderDriver::render_thread_func(const std::string& title, uint32_t width, uint32_t height)
{
    setup(title, width, height);
    run();
    cleanup();
    m_terminated = true;
}

void RenderDriver::setup(const std::string& title, uint32_t width, uint32_t height)
{
    // setup can't be performed twice at the same time
    lock lock {s_setup_mutex};
    MAKI_ASSERT_CRITICAL(!m_renderer, "Recreation of Renderer.");
    m_renderer = Renderer::create(title, width, height);
    MAKI_ASSERT_CRITICAL(!m_camera_driver, "Recreation of CameraDriver.");
    m_camera_driver = new CameraDriver(m_renderer);
    MAKI_ASSERT_CRITICAL(!m_cuboid_renderer, "Recreation of CuboidRenderer.");
    m_cuboid_renderer = new CuboidRenderer(m_renderer);
}

void RenderDriver::cleanup()
{
    MAKI_ASSERT_CRITICAL(m_renderer, "Renderer has already been deleted.");
    delete m_renderer;
    m_renderer = nullptr;
    MAKI_ASSERT_CRITICAL(m_camera_driver, "CameraDriver has already been deleted.");
    delete m_camera_driver;
    m_renderer = nullptr;
    MAKI_ASSERT_CRITICAL(m_cuboid_renderer, "CuboidRenderer has already been deleted.");
    delete m_cuboid_renderer;
    m_renderer = nullptr;
}

void RenderDriver::run()
{
    do {
        sync_frame_target();
        render_frame();
    } while(!m_renderer->should_terminate());
}

void RenderDriver::render_frame()
{
    m_camera_driver->update(m_renderer->get_last_frame_time());

    m_renderer->start_frame();

    m_cuboid_renderer->begin_scene(m_renderer->get_camera());
    for(size_t i {0}; i < m_render_cuboid_chain.size(); ++i) {
        m_cuboid_renderer->draw_atom(&m_render_cuboid_chain[i]);
    }
    m_cuboid_renderer->end_scene();

    render_imgui();
    m_renderer->end_frame();
}

void RenderDriver::render_imgui()
{
    // ImGui not thread-safe -> extra variables and locks required
    int   target_frame;
    float camera_speed {m_camera_driver->get_speed()};
    {
        lock lock {m_target_frame_mutex};
        target_frame = m_target_frame;
    }
    ImGui::Begin("Time Traveler's Toolkit");
    ImGui::Text("fps: %f", 1000.0 / m_renderer->get_last_frame_time());
    ImGui::SliderInt("Frame", &target_frame, 0, get_last_frame());
    ImGui::SliderFloat("Camera speed (units/ms)", &camera_speed, 0.001f, 0.5f);
    ImGui::End();
    {
        lock lock {m_target_frame_mutex};
        m_target_frame = target_frame;
    }
    m_camera_driver->set_speed(camera_speed);
}

// update frame to target
void RenderDriver::sync_frame_target()
{
    // TODO: jump-back could be optimized
    chrono_sync();
    lock lock {m_target_frame_mutex};
    m_render_cuboid_chain.set_frame(m_target_frame, m_cuboid_diff_lifetime);
}
// update rendering thread atom chains if necessary
void RenderDriver::chrono_sync()
{
    if(m_cuboid_diff_lifetime.is_outdated(m_render_cuboid_chain.get_frame())) {
        m_render_cuboid_chain.chrono_sync();
        m_cuboid_diff_lifetime.update();
    }
}

uint32_t RenderDriver::get_last_frame()
{
    // TODO: calculate max of all diff_lifetimes
    return m_cuboid_diff_lifetime.size() - 1;
}

} // namespace Maki
