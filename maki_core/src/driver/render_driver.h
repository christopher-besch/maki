#pragma once

#include <thread>

#include "atom/atom.h"
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

private:
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
    AtomChain<CuboidAtom> m_create_cuboid_ptr;
    // used by render thread
    AtomChain<CuboidAtom> m_render_cuboid_ptr;
    AtomDiffs<CuboidAtom> m_cuboid_diffs;

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
