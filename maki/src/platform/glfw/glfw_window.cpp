#if PROJECT == glfw
#include "pch.h"

#include "../window.h"
#include "core/log.h"
#include "renderer/renderer.h"

namespace Maki {

Window::~Window()
{
    glfwDestroyWindow(m_handle);
    --s_window_count;
    if(s_window_count == 0)
        glfwTerminate();
}

void Window::update()
{
    glfwSwapBuffers(m_handle);
    glfwPollEvents();
}

bool Window::should_close()
{
    return glfwWindowShouldClose(m_handle);
}

void Window::create()
{
    MAKI_LOG_EXTRA("Creating GLFW window '{0}' ({1}, {2}).", m_title, m_width, m_height);

    // 4x antialiasing
    glfwWindowHint(GLFW_SAMPLES, 4);
    // TODO: differentiate between OpenGL and Vulkan
    // OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    // for macos
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    // disable old OpenGL
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_handle = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
    ++s_window_count;
    if(m_handle == nullptr)
        MAKI_RAISE_CRITICAL("Failed to create GLFW window.");
    glfwMakeContextCurrent(m_handle);

    glfwSetWindowUserPointer(m_handle, this);

    bind_event_callbacks();
}

void Window::init()
{
    MAKI_LOG_EXTRA("Initializing GLFW.");

    int success = glfwInit();
    MAKI_ASSERT(success, "Couldn't initialize GLFW.");
    glfwSetErrorCallback([](int error, const char* description) {
        MAKI_LOG_ERROR("GLFW Error ({0}): {1}", error, description);
    });

#ifndef NDEBUG
    if(Renderer::get_renderer_api() == Renderer::Implementation::opengl)
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif
}

void Window::bind_event_callbacks()
{
    // std::function<bool(double offset_x, double offset_y)> m_on_scroll {nullptr};
    // std::function<bool(MouseBtn btn)>                     m_on_mouse_btn_pressed {nullptr};
    // std::function<bool(MouseBtn btn)>                     m_on_mouse_btn_release {nullptr};
    // std::function<bool(Key key)>                          m_on_key_pressed {nullptr};
    // std::function<bool(Key key)>                          m_on_key_repeated {nullptr};
    // std::function<bool(Key key)>                          m_on_key_release {nullptr};
    // std::function<bool(int width, int height)>            m_on_window_resize {nullptr};

    glfwSetCursorPosCallback(m_handle, [](GLFWwindow* handle, double x, double y) {
        Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(handle));
        // hand through layers until handled
        // only execute callback when not empty
        (window->m_renderer_event_handler.on_mouse_move && window->m_renderer_event_handler.on_mouse_move(x, y)) ||
            (window->m_driver_event_handler.on_mouse_move && window->m_driver_event_handler.on_mouse_move(x, y));
    });
}

} // namespace Maki
#endif
