#pragma once

#include "platform/window.h"
#include "renderer/index_buffer.h"
#include "renderer/shader.h"
#include "renderer/vertex_array.h"

namespace Maki {

class Renderer {
public:
    enum class Implementation {
        none    = 0,
        open_gl = 1
    };

public:
    // create renderer with implementation specified in s_renderer_impl
    // every implementation-specific class uses this concept
    static Renderer* create(const std::string& title, uint32_t width, uint32_t height);

public:
    Renderer(const std::string& title, uint32_t width, uint32_t height)
        : m_window(new Window(title, width, height)) {}
    virtual ~Renderer()
    {
        delete m_window;
    }

    static Implementation get_renderer_api() { return s_renderer_impl; }
    static void           set_renderer_api(Implementation renderer_impl) { s_renderer_impl = renderer_impl; }

    bool should_terminate()
    {
        return m_window->should_close();
    }

    virtual void draw(VertexArray* vertex_array, IndexBuffer* index_buffer, Shader* shader) = 0;

    virtual void end_frame() = 0;

protected:
    static inline Implementation s_renderer_impl {Renderer::Implementation::none};

protected:
    Window* m_window;
};

} // namespace Maki
