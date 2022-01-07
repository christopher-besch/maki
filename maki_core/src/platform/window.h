#pragma once

#if PROJECT == glfw
#include <GLFW/glfw3.h>
#endif
#include <imgui.h>
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

    // should be run before gl draws
    void start_frame();
    // should be run after gl draws
    void end_frame();

    void set_cursor_type(CursorType type);

    EventHandler& get_driver_event_handler() { return m_driver_event_handler; }

    bool imgui_supported() { return m_imgui_io; }

private:
    void create();
    // init performed at creation of first window
    void init();
    void bind_event_callbacks();
    // has to be called after bind_event_callbacks
    void init_imgui();

private:
    static inline int s_window_count {0};

private:
    std::string m_title;
    uint32_t    m_width, m_height;

    // only two layers supported
    EventHandler m_driver_event_handler, m_renderer_event_handler;

    // nullptr when imgui not supported -> only supported with first window because of https://github.com/ocornut/imgui/issues/2117
    ImGuiIO* m_imgui_io {nullptr};

#if PROJECT == glfw
    GLFWwindow* m_handle {nullptr};
#endif
};

} // namespace Maki
