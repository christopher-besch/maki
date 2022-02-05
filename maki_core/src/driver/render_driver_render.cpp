#include "pch.h"

#include "render_driver.h"

namespace Maki {

// all functions to be run from rendering thread
void RenderDriver::render_thread_func(const std::string& title, uint32_t width, uint32_t height, vec4 clear_col)
{
    MAKI_ASSERT_RNDR_THREAD();
    setup(title, width, height, clear_col);
    run();
    cleanup();
    m_terminated = true;
}

void RenderDriver::setup(const std::string& title, uint32_t width, uint32_t height, vec4 clear_col)
{
    MAKI_ASSERT_RNDR_THREAD();
    // setup can't be performed twice at the same time
    lock lock {s_setup_mutex};
    MAKI_ASSERT_CRITICAL(!m_renderer, "Recreation of Renderer.");
    m_renderer = Renderer::create(title, width, height, clear_col);
    MAKI_ASSERT_CRITICAL(!m_camera_driver, "Recreation of CameraDriver.");
    m_camera_driver = new CameraDriver(m_renderer);

    m_atom_dispenser.create_all_atom_renderers(m_renderer);
}

void RenderDriver::cleanup()
{
    MAKI_ASSERT_RNDR_THREAD();
    MAKI_ASSERT_CRITICAL(m_renderer, "Renderer has already been deleted.");
    delete m_renderer;
    m_renderer = nullptr;
    MAKI_ASSERT_CRITICAL(m_camera_driver, "CameraDriver has already been deleted.");
    delete m_camera_driver;
    m_camera_driver = nullptr;

    m_atom_dispenser.delete_all_renderers();
}

void RenderDriver::run()
{
    MAKI_ASSERT_RNDR_THREAD();
    do {
        render_frame();
    } while(!m_renderer->should_terminate());
}

void RenderDriver::render_frame()
{
    MAKI_ASSERT_RNDR_THREAD();
    sync_frame_target();
    m_camera_driver->update(m_renderer->get_last_frame_time());

    m_renderer->start_frame();
    m_atom_dispenser.render_all();
    render_imgui();
    m_renderer->end_frame();
}

void RenderDriver::render_imgui()
{
    MAKI_ASSERT_RNDR_THREAD();
    if(!m_renderer->imgui_supported())
        return;
    // ImGui not thread-safe -> extra variables and locks required
    int   target_frame;
    float camera_speed {m_camera_driver->get_speed()};
    {
        lock lock {m_target_frame_mutex};
        target_frame = m_target_frame;
    }
    ImGui::Begin("Time Traveler's Toolkit");
    ImGui::Text("fps: %f", 1000.0 / m_renderer->get_last_frame_time());
    ImGui::SliderInt("Frame", &target_frame, 0, m_atom_dispenser.get_last_frame());
    ImGui::SliderFloat("Camera speed (units/ms)", &camera_speed, 0.001f, 0.5f);
    if(ImGui::Button("Force Chrono Sync"))
        m_atom_dispenser.ensure_chrono_sync(true);
    ImGui::End();
    {
        lock lock {m_target_frame_mutex};
        m_target_frame = target_frame;
    }
    m_camera_driver->set_speed(camera_speed);
}

void RenderDriver::sync_frame_target()
{
    MAKI_ASSERT_RNDR_THREAD();
    m_atom_dispenser.ensure_chrono_sync();
    lock lock {m_target_frame_mutex};
    m_atom_dispenser.set_render_frame(m_target_frame);
}

} // namespace Maki
