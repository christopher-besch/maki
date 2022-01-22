#include "pch.h"

#include "render_driver.h"

namespace Maki {

// all functions to be run from control thread
mutex RenderDriver::s_setup_mutex;

RenderDriver::RenderDriver(const std::string& title, uint32_t width, uint32_t height)
{
    m_render_thread = std::thread([this, title, width, height]() {
        // only rendering thread code in this file
        render_thread_func(title, width, height);
    });
}

RenderDriver::~RenderDriver()
{
    MAKI_ASSERT_WARN(m_render_thread.joinable(), "Attempting termination of unjoinable render thread.");
    if(!m_terminated) {
        m_renderer->terminate();
        await_termination();
    }
}

void RenderDriver::await_termination()
{
    // not even running?
    if(!m_render_thread.joinable())
        return;
    m_render_thread.join();
}

void RenderDriver::set_target_frame(uint32_t frame)
{
    lock lock {m_target_frame_mutex};
    m_atom_dispenser.ensure_frame_existance(frame);
    m_target_frame = frame;
}

} // namespace Maki
