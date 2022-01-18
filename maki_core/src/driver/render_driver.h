#pragma once

#include <thread>

#include "atom/atom_chain.h"
#include "atom/atom_diff_lifetime.h"
#include "driver/camera_driver.h"
#include "driver/cuboid_renderer.h"
#include "renderer/renderer.h"

namespace Maki {

// main interface to client program
// creates atoms, applies diffs to atoms, starts/sops rendering (creates rendering thread)
class RenderDriver {
public:
    // to be run from control thread
    RenderDriver(const std::string& title, uint32_t width, uint32_t height);

    ~RenderDriver();

    void await_termination();
    bool is_terminated() { return m_terminated; }

    // return id of created atom
    // TODO: create AtomDispenser
    uint32_t add_cuboid_atom();
    void     render_cuboid_atom(uint32_t id, uint32_t frame, bool render);
    void     translate_cuboid_atom(uint32_t id, uint32_t frame, vec3 delta);
    void     color_cuboid_atom(uint32_t id, uint32_t frame, vec4 col);

    void set_frame(uint32_t frame);

private:
    // to be run from control thread
    // TODO: xD
    void prepare_cuboid_atomization(uint32_t id, uint32_t frame);
    void finalize_cuboid_atomization(uint32_t id, uint32_t frame, AtomDiff<CuboidAtom>* diff);

    // to be run from render thread
    void render_thread_func(const std::string& title, uint32_t width, uint32_t height);
    void setup(const std::string& title, uint32_t width, uint32_t height);
    void cleanup();
    void run();
    void render_frame();
    void render_imgui();

    void sync_frame_target();
    void chrono_sync();

    uint32_t get_last_frame();

private:
    std::thread m_render_thread;
    bool        m_terminated;
    // owned by renderering thread <- OpenGL context can only be current for one thread
    Renderer*       m_renderer {nullptr};
    CameraDriver*   m_camera_driver {nullptr};
    CuboidRenderer* m_cuboid_renderer {nullptr};

    // used by control thread
    AtomChain<CuboidAtom> m_control_cuboid_chain;
    // used by render thread
    AtomChain<CuboidAtom> m_render_cuboid_chain;

    AtomDiffLifetime<CuboidAtom> m_cuboid_diff_lifetime;

    uint32_t m_target_frame {0};
    mutex    m_target_frame_mutex;

private:
    static mutex s_setup_mutex;
};

} // namespace Maki
