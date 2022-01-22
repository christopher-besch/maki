#include "pch.h"

#include "atom_dispenser.h"

namespace Maki {

uint32_t AtomDispenser::get_last_frame()
{
    return m_cuboid_diff_lifetime.size() - 1;
}

AtomDispenser::~AtomDispenser()
{
    delete m_cuboid_renderer;
}

void AtomDispenser::create_all_renderers(Renderer* renderer)
{
    create_cuboid_renderer(renderer);
}

void AtomDispenser::render_all()
{
    render_cuboids();
}

void AtomDispenser::ensure_frame_existance(uint32_t frame)
{
    m_cuboid_diff_lifetime.ensure_frame_existence(frame);
}
void AtomDispenser::set_render_frame(uint32_t frame)
{
    m_render_cuboid_chain.set_frame(frame, m_cuboid_diff_lifetime);
}
void AtomDispenser::chrono_sync()
{
    individual_chrono_sync<CuboidAtom>();
}

// CuboidAtom
void AtomDispenser::create_cuboid_renderer(Renderer* renderer)
{
    MAKI_ASSERT_CRITICAL(!m_cuboid_renderer, "Recreation of CuboidRenderer.");
    m_cuboid_renderer = new CuboidRenderer(renderer);
}
void AtomDispenser::render_cuboids()
{
    m_cuboid_renderer->begin_scene();
    for(size_t i {0}; i < m_render_cuboid_chain.size(); ++i) {
        m_cuboid_renderer->draw_atom(&m_render_cuboid_chain[i]);
    }
    m_cuboid_renderer->end_scene();
}

} // namespace Maki
