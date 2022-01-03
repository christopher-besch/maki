#include "pch.h"

#include "renderer.h"

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
    : m_camera {new Camera(width, height)}, m_last_time {Clock::now()}
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

void Renderer::start_frame()
{
    TimePoint current_time = Clock::now();
    m_last_frame_time      = current_time - m_last_time;
    m_last_time            = current_time;
}
void Renderer::end_frame()
{
    m_window->end_frame();
}

} // namespace Maki
