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
    : m_camera {new Camera(width, height)}
{
    EventHandler renderer_event_handler;
    renderer_event_handler.on_window_resize = [this](int width, int height) {
        m_camera->set_window_size(width, height);
        set_viewport(0, 0, width, height);
        return false;
    };
    renderer_event_handler.on_window_close = [this]() {
        m_should_terminate = true;
        return false;
    };
    m_window = new Window(title, width, height, driver_event_handler, renderer_event_handler);
}

} // namespace Maki
