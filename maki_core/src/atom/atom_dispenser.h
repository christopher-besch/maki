#pragma once

#include "atom/atom_chain.h"
#include "atom/renderers/cuboid_renderer.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Maki {

class AtomDispenser {
public:
    ~AtomDispenser();

    // to be run from control thread //

    // return id of created atom
    template<typename AtomType>
    uint32_t add_atom()
    {
        // reason for why chains can't be thread_local
        uint32_t control_id = control_chain<AtomType>().add();
        uint32_t render_id  = render_chain<AtomType>().add();
        MAKI_ASSERT_CRITICAL(control_id == render_id, "Control (ID {}) and render (ID {}) {} chain out of sync.", control_id, render_id, AtomType::type_name);
        return control_id;
    }
    template<typename AtomType>
    void show_atom(uint32_t id, uint32_t frame, bool render)
    {
        prepare_update<AtomType>(id, frame);
        if(control_chain<AtomType>()[id].render != render) {
            const auto diff = new ToggleRenderDiff<AtomType>(id);
            finalize_update<AtomType>(id, frame, diff);
        }
    }
    template<typename AtomType>
    void translate_atom(uint32_t id, uint32_t frame, vec3 delta)
    {
        prepare_update<AtomType>(id, frame);
        auto diff = new TransformDiff<AtomType>(id, glm::translate(mat4 {1.0f}, delta));
        finalize_update<AtomType>(id, frame, diff);
    }
    template<typename AtomType>
    void color_atom(uint32_t id, uint32_t frame, vec4 col)
    {
        prepare_update<AtomType>(id, frame);
        // calculate difference
        std::array<vec4, 8> delta_col;
        delta_col.fill(col);
        for(size_t i {0}; i != delta_col.size(); ++i) {
            delta_col[i] -= control_chain<AtomType>()[id].ver_col[i];
        }
        auto diff = new ReColorDiff<AtomType>(id, delta_col);
        finalize_update<AtomType>(id, frame, diff);
    }

    // to be run from render thread //

    uint32_t get_last_frame();

    void create_all_renderers(Renderer* renderer);

    void render_all();

    void ensure_frame_existance(uint32_t frame);
    // update frame to target
    void set_render_frame(uint32_t frame);
    // update rendering thread atom chains if necessary
    void chrono_sync();

private:
    // atom dispensing //
    template<typename AtomType>
    AtomChain<AtomType>& control_chain();
    template<typename AtomType>
    AtomChain<AtomType>& render_chain();
    template<typename AtomType>
    AtomDiffLifetime<AtomType>& diff_lifetime();

    // to be run from control thread

    // set control frame -> set AtomChain to frame that should be effected
    template<typename AtomType>
    void prepare_update(uint32_t id, uint32_t frame)
    {
        MAKI_ASSERT_CRITICAL(control_chain<AtomType>().size() > id, "ID {} hasn't been allocated yet for {} atoms.", id, AtomType::type_name);
        // first frame can't have any diffs <- first frame used as reference for others
        MAKI_ASSERT_CRITICAL(frame > 0, "Frame {} is invalid.", frame);

        diff_lifetime<AtomType>().ensure_frame_existence(frame);
        control_chain<AtomType>().set_frame(frame, diff_lifetime<AtomType>());
    }
    // save new AtomDiff and apply it -> current AtomChain is correct
    template<typename AtomType>
    void finalize_update(uint32_t id, uint32_t frame, const AtomDiff<AtomType>* diff)
    {
        diff_lifetime<AtomType>().add(frame, diff);
        diff->apply(control_chain<AtomType>()[id]);
    }

    // to be run from render thread //

    // CuboidAtom
    void create_cuboid_renderer(Renderer* renderer);
    void render_cuboids();

    template<typename AtomType>
    void individual_chrono_sync()
    {
        if(diff_lifetime<AtomType>().is_outdated(render_chain<AtomType>().get_frame())) {
            render_chain<AtomType>().chrono_sync();
            diff_lifetime<AtomType>().update();
        }
    }

private:
    // used by control thread
    AtomChain<CuboidAtom> m_control_cuboid_chain {};
    // used by render thread
    AtomChain<CuboidAtom> m_render_cuboid_chain {};

    AtomDiffLifetime<CuboidAtom> m_cuboid_diff_lifetime {};

    CuboidRenderer* m_cuboid_renderer {nullptr};
};

// CuboidAtom
template<>
inline AtomChain<CuboidAtom>& AtomDispenser::control_chain<CuboidAtom>()
{
    return m_control_cuboid_chain;
}
template<>
inline AtomChain<CuboidAtom>& AtomDispenser::render_chain<CuboidAtom>()
{
    return m_render_cuboid_chain;
}
template<>
inline AtomDiffLifetime<CuboidAtom>& AtomDispenser::diff_lifetime<CuboidAtom>()
{
    return m_cuboid_diff_lifetime;
}

} // namespace Maki
