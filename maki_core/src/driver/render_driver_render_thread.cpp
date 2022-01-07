#include "pch.h"

#include "render_driver.h"

namespace Maki {

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
        m_cuboid_renderer->draw_cuboid(&m_render_cuboid_chain[i]);
    }
    m_cuboid_renderer->end_scene();
    m_renderer->end_frame();
}

void RenderDriver::sync_frame_target()
{
    chrono_sync();
    m_render_cuboid_chain.set_frame(m_target_frame, m_cuboid_diff_lifetime);
}
void RenderDriver::chrono_sync()
{
    if(m_cuboid_diff_lifetime.is_outdated(m_render_cuboid_chain.get_frame())) {
        m_render_cuboid_chain.chrono_sync();
        m_cuboid_diff_lifetime.update();
    }
}

} // namespace Maki
