#pragma once

#include "platform/event.h"
#include "platform/window.h"
#include "renderer/buffer.h"
#include "renderer/camera.h"
#include "renderer/shader.h"
#include "renderer/vertex_array.h"

namespace Maki {

// TODO: MAKI_ASSERT_RNDR_THREADs should be added, but not so clean with inheritance
// low-level abstraction for rendering api calls
// implementation gets chosen at runtime -> inheritance
class Renderer {
public:
    enum class Implementation {
        none   = 0,
        opengl = 1,
    };

public:
    // create renderer with implementation specified in s_renderer_impl
    // every implementation-specific class uses this concept
    static Renderer* create(const std::string& title, uint32_t width, uint32_t height, EventHandler driver_event_handler = EventHandler {});

    static Implementation get_renderer_impl() { return s_renderer_impl; }
    static void           set_renderer_impl(Implementation renderer_impl) { s_renderer_impl = renderer_impl; }

public:
    Renderer(const std::string& title, uint32_t width, uint32_t height, EventHandler driver_event_handler = EventHandler {});
    virtual ~Renderer();

    EventHandler& get_driver_event_handler() { return m_window->get_driver_event_handler(); }

    void set_cursor_type(CursorType type) { m_window->set_cursor_type(type); }

    Camera* get_camera() { return m_camera; }

    // in milliseconds
    long get_last_frame_time() { return get_mills(m_last_frame_time); }

    virtual void set_clear_col(vec4 color) = 0;

    // shader and vertex array object needs to be bound prior
    virtual void draw(uint32_t index_count) = 0;
    // to be augmented by implementation -> Renderer func has to be called from implementation prior to anything else
    virtual void start_frame();
    virtual void end_frame();

    // thread safe -> can be run from control thread //
    void terminate();
    bool should_terminate();

protected:
    static inline Implementation s_renderer_impl {Renderer::Implementation::none};

protected:
    Window* m_window {nullptr};
    Camera* m_camera {nullptr};
    // single source of truth for termination status
    // needs to be in renderer <- window close handled by renderer, otherwise reference to RenderDriver or other required, would be unclean
    bool  m_should_terminate {false};
    mutex m_should_terminate_mutex;

    TimePoint m_last_time;
    Duration  m_last_frame_time {0};
};

} // namespace Maki
