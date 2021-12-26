#pragma once

#include "platform/event.h"
#include "platform/window.h"
#include "renderer/buffer.h"
#include "renderer/shader.h"
#include "renderer/vertex_array.h"

namespace Maki {

class Renderer {
public:
    enum class Implementation {
        none   = 0,
        opengl = 1
    };

public:
    // create renderer with implementation specified in s_renderer_impl
    // every implementation-specific class uses this concept
    static Renderer* create(const std::string& title, uint32_t width, uint32_t height, EventHandler driver_event_handler);

    static Implementation get_renderer_api() { return s_renderer_impl; }
    static void           set_renderer_api(Implementation renderer_impl) { s_renderer_impl = renderer_impl; }

public:
    Renderer(const std::string& title, uint32_t width, uint32_t height, EventHandler driver_event_handler);
    virtual ~Renderer()
    {
        delete m_window;
    }

    virtual void set_clear_col(vec4 color)                                             = 0;
    virtual void set_viewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

    bool should_terminate() { return m_should_terminate; }

    virtual void draw(VertexArray* vertex_array, IndexBuffer* index_buffer, Shader* shader) = 0;
    virtual void start_frame()                                                              = 0;
    virtual void end_frame()                                                                = 0;

protected:
    static inline Implementation s_renderer_impl {Renderer::Implementation::none};

protected:
    Window* m_window;
    bool    m_should_terminate {false};
};

} // namespace Maki
