#include "pch.h"

#include "renderer.h"

#include "core/log.h"
#include "renderer/opengl/opengl_renderer.h"

namespace Maki {

Renderer* Renderer::create(const std::string& title, uint32_t width, uint32_t height, EventHandler driver_event_handler)
{
    switch(s_renderer_impl) {
    case Implementation::none:
        MAKI_RAISE_CRITICAL("Renderer::Implementation::none is not supported.");
        return nullptr;
    case Implementation::opengl:
        return new OpenGLRenderer(title, width, height, driver_event_handler);
    default:
        MAKI_RAISE_CRITICAL("The requested renderer implementation is not supported.");
        return nullptr;
    }
}

Renderer::Renderer(const std::string& title, uint32_t width, uint32_t height, EventHandler driver_event_handler)
{
    EventHandler renderer_event_handler;
    renderer_event_handler.on_window_resize = [](int width, int height) {
        MAKI_LOG_GENERAl("{} {}", width, height);
        return true;
    };
    m_window = new Window(title, width, height, driver_event_handler, renderer_event_handler);
}

} // namespace Maki
