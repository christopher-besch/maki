#include "pch.h"

#include "atom_dispenser.h"

namespace Maki {

AtomDispenser::~AtomDispenser()
{
    ASSERT_CONTROL_THREAD();
    MAKI_ASSERT_CRITICAL(!m_cuboid_renderer, "CuboidRenderer hasn't been deleted yet.");
    MAKI_ASSERT_CRITICAL(!m_quadrilateral_renderer, "QuadrilateralRenderer hasn't been deleted yet.");
}

uint32_t AtomDispenser::get_last_frame()
{
    ASSERT_RENDER_THREAD();
    return std::max(
               m_cuboid_diff_lifetime.size(),
               m_quadrilateral_diff_lifetime.size()) -
           1;
}

void AtomDispenser::create_all_renderers(Renderer* renderer)
{
    ASSERT_RENDER_THREAD();
    MAKI_ASSERT_CRITICAL(!m_cuboid_renderer, "Recreation of CuboidRenderer.");
    m_cuboid_renderer = new CuboidRenderer(renderer);

    MAKI_ASSERT_CRITICAL(!m_quadrilateral_renderer, "Recreation of QuadrilateralRenderer.");
    m_quadrilateral_renderer = new QuadrilateralRenderer(renderer);
}

void AtomDispenser::delete_all_renderers()
{
    ASSERT_RENDER_THREAD();
    MAKI_ASSERT_CRITICAL(m_cuboid_renderer, "Redeletion of CuboidRenderer.");
    delete m_cuboid_renderer;
    m_cuboid_renderer = nullptr;

    MAKI_ASSERT_CRITICAL(m_quadrilateral_renderer, "Redeletion of QuadrilateralRenderer.");
    delete m_quadrilateral_renderer;
    m_quadrilateral_renderer = nullptr;
}

void AtomDispenser::render_all()
{
    ASSERT_RENDER_THREAD();
    individual_render<CuboidAtom>();

    individual_render<QuadrilateralAtom>();
}

void AtomDispenser::set_render_frame(uint32_t frame)
{
    ASSERT_RENDER_THREAD();
    m_render_cuboid_chain.set_frame(frame, m_cuboid_diff_lifetime);

    m_render_quadrilateral_chain.set_frame(frame, m_quadrilateral_diff_lifetime);
}
void AtomDispenser::chrono_sync()
{
    ASSERT_RENDER_THREAD();
    individual_chrono_sync<CuboidAtom>();

    individual_chrono_sync<QuadrilateralAtom>();
}

void AtomDispenser::ensure_frame_existence(uint32_t frame)
{
    m_cuboid_diff_lifetime.ensure_frame_existence(frame);

    m_quadrilateral_diff_lifetime.ensure_frame_existence(frame);
}

} // namespace Maki
