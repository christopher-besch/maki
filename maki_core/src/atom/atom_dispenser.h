#pragma once

#include "atom/atom_chain.h"
#include "atom/atom_renderer.h"
#include "core/definitions.h"
#include "core/thread_safety.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Maki {

class AtomDispenser {
public:
    // to be run from control thread //

    ~AtomDispenser();

    // return id of created atom
    template<typename AtomType>
    uint32_t add_atom()
    {
        MAKI_ASSERT_CTRL_THREAD();
        // reason for why chains can't be thread_local
        uint32_t control_id = get_control_chain<AtomType>().add();
        uint32_t render_id  = get_render_chain<AtomType>().add();
        MAKI_ASSERT_CRITICAL(control_id == render_id, "Control (ID {}) and render (ID {}) {} chain out of sync.", control_id, render_id, AtomType::type_name);
        return control_id;
    }
    template<typename AtomType>
    void show_atom(uint32_t id, uint32_t frame, bool render)
    {
        MAKI_ASSERT_CTRL_THREAD();
        // TODO: prepare_update locks m_atoms_mutex and get_locked_atom locks it again -> inefficient
        prepare_update<AtomType>(id, frame);
        auto [lock, atom] = get_control_chain<AtomType>().get_locked_atom(id);
        if(atom.render != render) {
            // ownsership is taken over by AtomDiffFrame
            const auto diff = new ToggleRenderDiff<AtomType>(id);
            finalize_update<AtomType>(frame, atom, diff);
        }
    }
    template<typename AtomType>
    void translate_atom(uint32_t id, uint32_t frame, vec3 delta)
    {
        MAKI_ASSERT_CTRL_THREAD();
        prepare_update<AtomType>(id, frame);
        auto [lock, atom] = get_control_chain<AtomType>().get_locked_atom(id);
        auto diff         = new TransformDiff<AtomType>(id, glm::translate(mat4 {1.0f}, delta));
        finalize_update<AtomType>(frame, atom, diff);
    }
    template<typename AtomType>
    void color_atom(uint32_t id, uint32_t frame, vec4 col)
    {
        MAKI_ASSERT_CTRL_THREAD();
        prepare_update<AtomType>(id, frame);
        auto [lock, atom] = get_control_chain<AtomType>().get_locked_atom(id);
        // calculate difference
        std::array<vec4, AtomType::vertex_count> delta_col;
        delta_col.fill(col);
        for(size_t i {0}; i != delta_col.size(); ++i) {
            delta_col[i] -= atom.ver_col[i];
        }
        auto diff = new ReColorDiff<AtomType>(id, delta_col);
        finalize_update<AtomType>(frame, atom, diff);
    }

    // to be run from render thread //

    uint32_t get_last_frame();

    // can't be performed in constructor <- constructed with main thread, renderer using OpenGL calls -> need to be called from render thread
    void create_all_atom_renderers(Renderer* renderer);
    // same with destructor
    void delete_all_renderers();

    void render_all();

    // update frame to target
    void set_render_frame(uint32_t frame);
    // update rendering thread atom chains if necessary
    void ensure_chrono_sync(bool force = false);

    // can ben run from both threads //

    void ensure_frame_existence(uint32_t frame);

private:
    // atom dispensing -> return requested variable in template specialization //
    template<typename AtomType>
    AtomChain<AtomType>& get_control_chain();
    template<typename AtomType>
    AtomChain<AtomType>& get_render_chain();
    template<typename AtomType>
    AtomDiffLifetime<AtomType>& get_diff_lifetime();
    // ::type notation required because renderers are implemented using OOP -> generic programming interface layer required
    template<typename AtomType>
    typename AtomRendererRouter<AtomType>::type* get_renderer();

    // to be run from control thread

    // set control frame -> set AtomChain to frame that should be effected
    template<typename AtomType>
    void prepare_update(uint32_t id, uint32_t frame)
    {
        MAKI_ASSERT_CTRL_THREAD();
        MAKI_ASSERT_CRITICAL(get_control_chain<AtomType>().size() > id, "ID {} hasn't been allocated yet for {} atoms.", id, AtomType::type_name);
        // first frame can't have any diffs <- first frame used as reference for others
        MAKI_ASSERT_CRITICAL(frame > 0, "Frame {} is invalid.", frame);

        ensure_frame_existence(frame);
        get_control_chain<AtomType>().set_frame(frame, get_diff_lifetime<AtomType>());
    }
    // save new AtomDiff and apply it -> current AtomChain is correct
    template<typename AtomType>
    void finalize_update(uint32_t frame, AtomType& atom, const AtomDiff<AtomType>* diff)
    {
        MAKI_ASSERT_CTRL_THREAD();
        get_diff_lifetime<AtomType>().add(frame, diff);
        diff->apply(atom);
    }

    // to be run from render thread //

    template<typename AtomType>
    void ensure_individual_chrono_sync(bool force)
    {
        MAKI_ASSERT_RNDR_THREAD();
        if(force || get_diff_lifetime<AtomType>().is_outdated(get_render_chain<AtomType>().get_frame())) {
            get_render_chain<AtomType>().chrono_sync();
            get_diff_lifetime<AtomType>().update();
        }
    }

    template<typename AtomType>
    void individual_render()
    {
        MAKI_ASSERT_RNDR_THREAD();
        get_render_chain<AtomType>().render(get_renderer<AtomType>());
    }

private:
    // CuboidAtom
    // used by control thread or render thread respectively
    AtomChain<CuboidAtom>        m_control_cuboid_chain {};
    AtomChain<CuboidAtom>        m_render_cuboid_chain {};
    AtomDiffLifetime<CuboidAtom> m_cuboid_diff_lifetime {};
    CuboidRenderer*              m_cuboid_renderer {nullptr};
    // QuadrilateralAtom
    AtomChain<QuadrilateralAtom>        m_control_quadrilateral_chain {};
    AtomChain<QuadrilateralAtom>        m_render_quadrilateral_chain {};
    AtomDiffLifetime<QuadrilateralAtom> m_quadrilateral_diff_lifetime {};
    QuadrilateralRenderer*              m_quadrilateral_renderer {nullptr};
};

// CuboidAtom
template<>
inline AtomChain<CuboidAtom>& AtomDispenser::get_control_chain<CuboidAtom>()
{
    return m_control_cuboid_chain;
}
template<>
inline AtomChain<CuboidAtom>& AtomDispenser::get_render_chain<CuboidAtom>()
{
    return m_render_cuboid_chain;
}
template<>
inline AtomDiffLifetime<CuboidAtom>& AtomDispenser::get_diff_lifetime<CuboidAtom>()
{
    return m_cuboid_diff_lifetime;
}
template<>
inline AtomRendererRouter<CuboidAtom>::type* AtomDispenser::get_renderer<CuboidAtom>()
{
    return m_cuboid_renderer;
}

// QuadrilateralAtom
template<>
inline AtomChain<QuadrilateralAtom>& AtomDispenser::get_control_chain<QuadrilateralAtom>()
{
    return m_control_quadrilateral_chain;
}
template<>
inline AtomChain<QuadrilateralAtom>& AtomDispenser::get_render_chain<QuadrilateralAtom>()
{
    return m_render_quadrilateral_chain;
}
template<>
inline AtomDiffLifetime<QuadrilateralAtom>& AtomDispenser::get_diff_lifetime<QuadrilateralAtom>()
{
    return m_quadrilateral_diff_lifetime;
}
template<>
inline QuadrilateralRenderer* AtomDispenser::get_renderer<QuadrilateralAtom>()
{
    return m_quadrilateral_renderer;
}

} // namespace Maki
