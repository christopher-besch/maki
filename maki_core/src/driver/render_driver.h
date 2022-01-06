#pragma once

#include <thread>

#include "atom/container.h"
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

private:
    // to be run from control thread
    void set_control_frame(uint32_t frame);

    // to be run from render thread
    void setup();
    void run();
    void render_frame();
    bool imgui_support() { return m_renderer->imgui_supported(); }

private:
    std::thread m_render_thread;
    bool        m_terminated;
    // owned by renderering thread <- OpenGL context can only be current for one thread
    Renderer*     m_renderer;
    CameraDriver* m_camera_driver;

    // used by control thread
    AtomChain<CuboidAtom> m_control_cuboid_chain;
    // used by render thread
    // AtomChain<CuboidAtom> m_render_cuboid_chain;

    AtomDiffFrames<CuboidAtom> m_cuboid_diff_frames;

    // TODO: remove example
    Shader*       m_shader;
    VertexBuffer* m_vertex_pos_buffer;
    VertexBuffer* m_vertex_col_buffer;
    VertexArray*  m_vertex_array;
    IndexBuffer*  m_index_buffer;

private:
    static std::mutex s_setup_mutex;
};

} // namespace Maki
