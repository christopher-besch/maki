#include "pch.h"

#include "renderer.h"

#include "renderer/opengl/opengl_renderer.h"

namespace Maki {

Renderer* Renderer::create(const std::string& title, uint32_t width, uint32_t height, vec4 clear_col, EventHandler driver_event_handler)
{
    switch(s_renderer_impl) {
    case Implementation::none:
        MAKI_RAISE_CRITICAL("Renderer::Implementation::none is not supported.");
        return nullptr;
    case Implementation::opengl:
        return new OpenGLRenderer(title, width, height, clear_col, driver_event_handler);
    default:
        MAKI_RAISE_CRITICAL("The requested renderer implementation is not supported.");
        return nullptr;
    }
}

Renderer::Renderer(const std::string& title, uint32_t width, uint32_t height, EventHandler driver_event_handler)
    : m_camera {new Camera(width, height, Camera::Type::perspective)}, m_last_time {Clock::now()}
{
    EventHandler renderer_event_handler;
    renderer_event_handler.on_window_resize = [this](int width, int height) {
        m_camera->set_window_size(width, height);
        return false;
    };
    renderer_event_handler.on_window_close = [this]() {
        terminate();
        return false;
    };
    m_window = new Window(title, width, height, driver_event_handler, renderer_event_handler);
}

Renderer::~Renderer()
{
    delete m_window;
    delete m_camera;
}

void Renderer::start_frame()
{
    TimePoint current_time = Clock::now();
    m_last_frame_time      = current_time - m_last_time;
    m_last_time            = current_time;
    m_window->start_frame();
}
void Renderer::end_frame()
{
    m_window->end_frame();
}

// thread safe -> can be run from control thread //
void Renderer::terminate()
{
    lock lock {m_should_terminate_mutex};
    m_should_terminate = true;
}
bool Renderer::should_terminate()
{
    lock lock {m_should_terminate_mutex};
    return m_should_terminate;
}

} // namespace Maki
