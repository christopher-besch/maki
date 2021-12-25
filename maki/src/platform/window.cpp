#include "pch.h"

#include "renderer/renderer.h"
#include "window.h"

namespace Maki {

Window::Window(const std::string& title, uint32_t width, uint32_t height, EventHandler driver_event_handler, EventHandler renderer_event_handler)
    : m_title(title), m_width(width), m_height(height), m_driver_event_handler(driver_event_handler), m_renderer_event_handler(renderer_event_handler)
{
    // check compatibility
#if PROJECT == glfw
    MAKI_ASSERT(
        Renderer::get_renderer_api() == Renderer::Implementation::opengl,
        "Unsupported Implementation for a GLFW Window.");
#endif
    if(s_window_count == 0)
        init();
    create();
}

} // namespace Maki
