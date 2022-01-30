#include "pch.h"

#include "render_driver.h"

namespace Maki {

// all functions to be run from control thread
mutex RenderDriver::s_setup_mutex;

RenderDriver::RenderDriver(const std::string& title, uint32_t width, uint32_t height, vec4 clear_color)
{
    MAKI_ASSERT_CTRL_THREAD();
    m_render_thread = std::thread([this, title, width, height, clear_color]() {
        SET_THREAD_TYPE_RENDER();
        // only render thread code in this file
        render_thread_func(title, width, height, clear_color);
    });
}

RenderDriver::~RenderDriver()
{
    MAKI_ASSERT_CTRL_THREAD();
    MAKI_ASSERT_WARN(m_render_thread.joinable(), "Attempting termination of unjoinable render thread.");
    if(!m_terminated) {
        m_renderer->terminate();
        await_termination();
    }

    // ensure cleanup has been called
    MAKI_ASSERT_CRITICAL(!m_renderer, "Renderer hasn't been deleted yet.");
    MAKI_ASSERT_CRITICAL(!m_camera_driver, "CameraDriver hasn't been deleted yet.");
}

void RenderDriver::await_termination()
{
    MAKI_ASSERT_CTRL_THREAD();
    // not even running?
    if(!m_render_thread.joinable())
        return;
    m_render_thread.join();
}
bool RenderDriver::is_terminated()
{
    MAKI_ASSERT_CTRL_THREAD();
    return m_terminated;
}

void RenderDriver::set_target_frame(uint32_t frame)
{
    MAKI_ASSERT_CTRL_THREAD();
    lock lock {m_target_frame_mutex};
    m_atom_dispenser.ensure_frame_existence(frame);
    m_target_frame = frame;
}

} // namespace Maki
