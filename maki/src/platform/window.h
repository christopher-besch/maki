#pragma once

#include <GLFW/glfw3.h>
#include <iostream>

#include "core/log.h"
#include "platform/event.h"

namespace Maki {

class Window {
public:
    Window(const std::string& title, uint32_t width, uint32_t height, EventHandler driver_event_handler, EventHandler renderer_event_handler);
    ~Window();

    // should be run after gl draws
    void update();

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
