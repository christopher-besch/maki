#include "pch.h"

#include "atom_dispenser.h"

namespace Maki {

AtomDispenser::~AtomDispenser()
{
    ASSERT_CONTROL_THREAD();
    MAKI_ASSERT_CRITICAL(!m_cuboid_renderer, "CuboidRenderer hasn't been deleted yet.");
}

uint32_t AtomDispenser::get_last_frame()
{
    ASSERT_RENDER_THREAD();
    return m_cuboid_diff_lifetime.size() - 1;
}

void AtomDispenser::create_all_renderers(Renderer* renderer)
{
    ASSERT_RENDER_THREAD();
    MAKI_ASSERT_CRITICAL(!m_cuboid_renderer, "Recreation of CuboidRenderer.");
    m_cuboid_renderer = new CuboidRenderer(renderer);
}

void AtomDispenser::delete_all_renderers()
{
    ASSERT_RENDER_THREAD();
    MAKI_ASSERT_CRITICAL(m_cuboid_renderer, "Redeletion of CuboidRenderer.");
    delete m_cuboid_renderer;
    m_cuboid_renderer = nullptr;
}

void AtomDispenser::render_all()
{
    ASSERT_RENDER_THREAD();
    render_cuboids();
}

void AtomDispenser::ensure_frame_existance(uint32_t frame)
{
    ASSERT_RENDER_THREAD();
    m_cuboid_diff_lifetime.ensure_frame_existence(frame);
}
void AtomDispenser::set_render_frame(uint32_t frame)
{
    ASSERT_RENDER_THREAD();
    m_render_cuboid_chain.set_frame(frame, m_cuboid_diff_lifetime);
}
void AtomDispenser::chrono_sync()
{
    ASSERT_RENDER_THREAD();
    individual_chrono_sync<CuboidAtom>();
}

// CuboidAtom
void AtomDispenser::render_cuboids()
{
    ASSERT_RENDER_THREAD();
    m_cuboid_renderer->begin_scene();
    for(size_t i {0}; i < m_render_cuboid_chain.size(); ++i) {
        m_cuboid_renderer->draw_atom(&m_render_cuboid_chain[i]);
    }
    m_cuboid_renderer->end_scene();
}

} // namespace Maki
