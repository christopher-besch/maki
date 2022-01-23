#include "pch.h"

#include "render_driver.h"

namespace Maki {

// all functions to be run from control thread
mutex RenderDriver::s_setup_mutex;

RenderDriver::RenderDriver(const std::string& title, uint32_t width, uint32_t height)
{
    ASSERT_CONTROL_THREAD();
    m_render_thread = std::thread([this, title, width, height]() {
        SET_THREAD_TYPE_RENDER();
        // only rendering thread code in this file
        render_thread_func(title, width, height);
    });
}

RenderDriver::~RenderDriver()
{
    ASSERT_CONTROL_THREAD();
    MAKI_ASSERT_WARN(m_render_thread.joinable(), "Attempting termination of unjoinable render thread.");
    if(!m_terminated) {
        m_renderer->terminate();
        await_termination();
    }
}

void RenderDriver::await_termination()
{
    ASSERT_CONTROL_THREAD();
    // not even running?
    if(!m_render_thread.joinable())
        return;
    m_render_thread.join();
}
bool RenderDriver::is_terminated()
{
    ASSERT_CONTROL_THREAD();
    return m_terminated;
}

void RenderDriver::set_target_frame(uint32_t frame)
{
    ASSERT_CONTROL_THREAD();
    lock lock {m_target_frame_mutex};
    m_atom_dispenser.ensure_frame_existence(frame);
    m_target_frame = frame;
}

} // namespace Maki
