#pragma once
#include <thread>

#include "driver/camera_driver.h"
#include "renderer/renderer.h"

namespace Maki {

class RenderThread {
public:
    // to be run from control thread
    // WARN: termination_callback is being called from render thread
    RenderThread(const std::string& title, uint32_t width, uint32_t height, std::function<void()> termination_callback);

    ~RenderThread();

    void await_termination();

private:
    // to be run from render thread
    void setup();
    void run();
    void render_frame();

private:
    std::thread m_thread;
    // owned by renderering thread <- OpenGL context can only be current for one thread
    Renderer*     m_renderer;
    CameraDriver* m_camera_driver;

    std::function<void()> m_termination_callback;

    // TODO: remove example
    Shader*       m_shader;
    VertexBuffer* m_vertex_pos_buffer;
    VertexBuffer* m_vertex_col_buffer;
    VertexArray*  m_vertex_array;
    IndexBuffer*  m_index_buffer;
};

} // namespace Maki
