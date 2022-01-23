#pragma once

#include <thread>

#include "atom/atom_dispenser.h"
#include "driver/camera_driver.h"
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
    bool is_terminated();

    // return id of created atom
    template<typename AtomType>
    uint32_t add_atom()
    {
        ASSERT_CONTROL_THREAD();
        return m_atom_dispenser.add_atom<AtomType>();
    }

    template<typename AtomType>
    void show_atom(uint32_t id, uint32_t frame, bool show)
    {
        ASSERT_CONTROL_THREAD();
        return m_atom_dispenser.show_atom<AtomType>(id, frame, show);
    }
    template<typename AtomType>
    void translate_atom(uint32_t id, uint32_t frame, vec3 delta)
    {
        ASSERT_CONTROL_THREAD();
        m_atom_dispenser.translate_atom<AtomType>(id, frame, delta);
    }
    template<typename AtomType>
    void color_atom(uint32_t id, uint32_t frame, vec4 col)
    {
        ASSERT_CONTROL_THREAD();
        m_atom_dispenser.color_atom<AtomType>(id, frame, col);
    }

    void set_target_frame(uint32_t frame);

private:
    // to be run from render thread
    void render_thread_func(const std::string& title, uint32_t width, uint32_t height);
    void setup(const std::string& title, uint32_t width, uint32_t height);
    void cleanup();
    void run();
    void render_frame();
    void render_imgui();

    // update frame to match target
    void sync_frame_target();

private:
    std::thread m_render_thread;
    bool        m_terminated;
    // owned by renderering thread <- OpenGL context can only be current for one thread
    Renderer*     m_renderer {nullptr};
    CameraDriver* m_camera_driver {nullptr};

    AtomDispenser m_atom_dispenser {};

    uint32_t m_target_frame {0};
    mutex    m_target_frame_mutex;

private:
    static mutex s_setup_mutex;
};

} // namespace Maki
