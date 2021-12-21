#include "pch.h"

#include "renderer/renderer.h"
#include "window.h"

namespace Maki {

int Window::s_window_count {0};

Window::Window(const std::string& title, uint32_t width, uint32_t height)
    : m_title(title), m_width(width), m_height(height)
{
    // check compatibility
#if PROJECT == glfw
    MAKI_ASSERT(
        Renderer::get_renderer_api() == Renderer::Implementation::open_gl,
        "Unsupported Implementation for a GLFW Window.");
#endif
    if(s_window_count == 0)
        init();
    create();
}

} // namespace Maki
