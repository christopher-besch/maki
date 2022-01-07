#pragma once

#include <thread>

#include "atom/atom_chain.h"
#include "atom/atom_diff_lifetime.h"
#include "driver/camera_driver.h"
#include "driver/cuboid_renderer.h"
#include "renderer/renderer.h"

namespace Maki {

class RenderDriver {
public:
    // to be run from control thread
    RenderDriver(const std::string& title, uint32_t width, uint32_t height);

    ~RenderDriver();

    void await_termination();
    bool is_terminated() { return m_terminated; }

    // return id of created atom
    uint32_t add_cuboid_atom();
    void     render_cuboid_atom(uint32_t id, uint32_t frame, bool render);
    void     translate_cuboid_atom(uint32_t id, uint32_t frame, vec3 delta);

    void set_frame(uint32_t frame);

private:
    // to be run from render thread
    void render_thread_func(const std::string& title, uint32_t width, uint32_t height);
    void setup(const std::string& title, uint32_t width, uint32_t height);
    void cleanup();
    void run();
    void render_frame();
    bool imgui_support() { return m_renderer->imgui_supported(); }

    void sync_frame_target();
    void chrono_sync();

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
