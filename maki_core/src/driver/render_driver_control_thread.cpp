#include "pch.h"

#include "render_driver.h"

namespace Maki {

mutex RenderDriver::s_setup_mutex;

RenderDriver::RenderDriver(const std::string& title, uint32_t width, uint32_t height)
{
    m_render_thread = std::thread([this, title, width, height]() {
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

void RenderDriver::set_frame(uint32_t frame)
{
    lock lock {m_target_frame_mutex};
    m_cuboid_diff_lifetime.ensure_frame_existence(frame);
    m_target_frame = frame;
}

uint32_t RenderDriver::add_cuboid_atom()
{
    uint32_t control_id = m_control_cuboid_chain.add();
    uint32_t render_id  = m_render_cuboid_chain.add();
    MAKI_ASSERT_CRITICAL(control_id == render_id, "Control (ID {}) and render (ID {}) cuboid chain out of sync.", control_id, render_id);
    return control_id;
}
// TODO: OOP approach might be less painful for Python
void RenderDriver::render_cuboid_atom(uint32_t id, uint32_t frame, bool render)
{
    MAKI_ASSERT_CRITICAL(m_control_cuboid_chain.size() > id, "ID {} for CuboidAtoms hasn't been allocated yet.", id);
    // first frame can't have any diffs <- first frame used as reference for others
    MAKI_ASSERT_CRITICAL(frame > 0, "Frame {} is invalid.", frame);

    m_cuboid_diff_lifetime.ensure_frame_existence(frame);
    m_control_cuboid_chain.set_frame(frame, m_cuboid_diff_lifetime);

    if(m_control_cuboid_chain[id].render != render) {
        auto diff = new ToggleRenderDiff<CuboidAtom>(id);
        m_cuboid_diff_lifetime.add(frame, diff);
        diff->apply(m_control_cuboid_chain[id]);
    }
}
void RenderDriver::translate_cuboid_atom(uint32_t id, uint32_t frame, vec3 delta)
{
}

} // namespace Maki
