#pragma once

#include <thread>

#include "atom/atom_chain.h"
#include "atom/atom_diff_lifetime.h"
#include "driver/camera_driver.h"
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
    void run();
    void render_frame();
    bool imgui_support() { return m_renderer->imgui_supported(); }

    void sync_frame_target();
    void chrono_sync();

private:
    std::thread m_render_thread;
    bool        m_terminated;
    // owned by renderering thread <- OpenGL context can only be current for one thread
    Renderer*     m_renderer;
    CameraDriver* m_camera_driver;

    // used by control thread
    AtomChain<CuboidAtom> m_control_cuboid_chain;
    // used by render thread
    AtomChain<CuboidAtom> m_render_cuboid_chain;

    AtomDiffLifetime<CuboidAtom> m_cuboid_diff_lifetime;

    uint32_t m_target_frame {0};
    mutex    m_target_frame_mutex;

    // TODO: remove example
    Shader*       m_shader;
    VertexBuffer* m_vertex_pos_buffer;
    VertexBuffer* m_vertex_col_buffer;
    VertexArray*  m_vertex_array;
    IndexBuffer*  m_index_buffer;

private:
    static mutex s_setup_mutex;
};

} // namespace Maki
