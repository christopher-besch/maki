#include "pch.h"

#include "render_driver.h"

namespace Maki {

void RenderDriver::render_thread_func(const std::string& title, uint32_t width, uint32_t height)
{
    setup(title, width, height);
    run();
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
    m_renderer->end_frame();
}

void RenderDriver::sync_frame_target()
{
    chrono_sync();
    m_render_cuboid_chain.set_frame(m_target_frame, m_cuboid_diff_lifetime);
}
void RenderDriver::chrono_sync()
{
    if(m_cuboid_diff_lifetime.get_first_outdated_frame() <= m_render_cuboid_chain.get_frame())
        m_render_cuboid_chain.chrono_sync();
}

} // namespace Maki
