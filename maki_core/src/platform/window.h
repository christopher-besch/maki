#pragma once

#include <GLFW/glfw3.h>
#include <iostream>

#include "core/log.h"
#include "platform/event.h"

namespace Maki {

enum class CursorType {
#if PROJECT == glfw
    normal   = GLFW_CURSOR_NORMAL,
    hidden   = GLFW_CURSOR_HIDDEN,
    disabled = GLFW_CURSOR_DISABLED,
#endif
};

class Window {
public:
    Window(const std::string& title, uint32_t width, uint32_t height, EventHandler driver_event_handler, EventHandler renderer_event_handler);
    ~Window();

    // should be run after gl draws
    void end_frame();

    void set_cursor_type(CursorType type);

    EventHandler get_driver_event_handler() { return m_driver_event_handler; }
    void         set_driver_event_handler(EventHandler driver_event_handler) { m_driver_event_handler = driver_event_handler; }

private:
    void create();
    // init performed at creation of first window
    void init();

    void bind_event_callbacks();

private:
    static inline int s_window_count {0};

private:
    std::string m_title;
    uint32_t    m_width, m_height;

    // only two layers supported
    EventHandler m_driver_event_handler, m_renderer_event_handler;

#if PROJECT == glfw
    GLFWwindow* m_handle;
#endif
};

} // namespace Maki
