#pragma once

#include "platform/event.h"
#include "platform/window.h"
#include "renderer/buffer.h"
#include "renderer/camera.h"
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
    static Renderer* create(const std::string& title, uint32_t width, uint32_t height, EventHandler driver_event_handler = EventHandler {});

    static Implementation get_renderer_impl() { return s_renderer_impl; }
    static void           set_renderer_impl(Implementation renderer_impl) { s_renderer_impl = renderer_impl; }

public:
    Renderer(const std::string& title, uint32_t width, uint32_t height, EventHandler driver_event_handler = EventHandler {});
    virtual ~Renderer()
    {
        delete m_window;
        delete m_camera;
    }

    EventHandler& get_driver_event_handler() { return m_window->get_driver_event_handler(); }

    void set_cursor_type(CursorType type) { m_window->set_cursor_type(type); }

    Camera* get_camera() { return m_camera; }

    // in milliseconds
    long get_last_frame_time() { return get_mills(m_last_frame_time); }

    virtual void set_clear_col(vec4 color) = 0;

    bool should_terminate() { return m_should_terminate; }

    virtual void draw(VertexArray* vertex_array, IndexBuffer* index_buffer, Shader* shader) = 0;
    // to be augmented by implementation -> Renderer func have to be called from implementation
    virtual void start_frame();
    virtual void end_frame();

protected:
    virtual void set_viewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

protected:
    static inline Implementation s_renderer_impl {Renderer::Implementation::none};

protected:
    Window* m_window;
    Camera* m_camera;
    bool    m_should_terminate {false};

    TimePoint m_last_time;
    Duration  m_last_frame_time {0};
};

} // namespace Maki
