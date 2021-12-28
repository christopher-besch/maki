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

void Window::end_frame()
{
    glfwSwapBuffers(m_handle);
    glfwPollEvents();
}

void Window::set_cursor_type(CursorType type)
{
    // TODO: add function for other modes
    glfwSetInputMode(m_handle, GLFW_CURSOR, static_cast<int>(type));
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
    glfwSetCursorPosCallback(m_handle, [](GLFWwindow* handle, double pos_x, double pos_y) {
        Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(handle));
        // propagate through layers until handled
        // only execute callback when not empty
        (window->m_renderer_event_handler.on_mouse_move && window->m_renderer_event_handler.on_mouse_move(pos_x, pos_y)) ||
            (window->m_driver_event_handler.on_mouse_move && window->m_driver_event_handler.on_mouse_move(pos_x, pos_y));
    });
    glfwSetScrollCallback(m_handle, [](GLFWwindow* handle, double offset_x, double offset_y) {
        Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(handle));
        (window->m_renderer_event_handler.on_scroll && window->m_renderer_event_handler.on_scroll(offset_x, offset_y)) ||
            (window->m_driver_event_handler.on_scroll && window->m_driver_event_handler.on_scroll(offset_x, offset_y));
    });
    glfwSetMouseButtonCallback(m_handle, [](GLFWwindow* handle, int button, int action, int) {
        Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(handle));
        switch(action) {
        case GLFW_PRESS:
            (window->m_renderer_event_handler.on_mouse_btn_press && window->m_renderer_event_handler.on_mouse_btn_press(static_cast<MouseBtn>(button))) ||
                (window->m_driver_event_handler.on_mouse_btn_press && window->m_driver_event_handler.on_mouse_btn_press(static_cast<MouseBtn>(button)));
            return;
        case GLFW_RELEASE:
            (window->m_renderer_event_handler.on_mouse_btn_release && window->m_renderer_event_handler.on_mouse_btn_release(static_cast<MouseBtn>(button))) ||
                (window->m_driver_event_handler.on_mouse_btn_release && window->m_driver_event_handler.on_mouse_btn_release(static_cast<MouseBtn>(button)));
            return;
        }
    });
    glfwSetKeyCallback(m_handle, [](GLFWwindow* handle, int key, int, int action, int) {
        Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(handle));
        switch(action) {
        case GLFW_PRESS:
            (window->m_renderer_event_handler.on_key_press && window->m_renderer_event_handler.on_key_press(static_cast<Key>(key))) ||
                (window->m_driver_event_handler.on_key_press && window->m_driver_event_handler.on_key_press(static_cast<Key>(key)));
            return;
        case GLFW_RELEASE:
            (window->m_renderer_event_handler.on_key_release && window->m_renderer_event_handler.on_key_release(static_cast<Key>(key))) ||
                (window->m_driver_event_handler.on_key_release && window->m_driver_event_handler.on_key_release(static_cast<Key>(key)));
            return;
        case GLFW_REPEAT:
            (window->m_renderer_event_handler.on_key_repeat && window->m_renderer_event_handler.on_key_repeat(static_cast<Key>(key))) ||
                (window->m_driver_event_handler.on_key_repeat && window->m_driver_event_handler.on_key_repeat(static_cast<Key>(key)));
            return;
        }
    });
    glfwSetWindowSizeCallback(m_handle, [](GLFWwindow* handle, int width, int height) {
        Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(handle));
        (window->m_renderer_event_handler.on_window_resize && window->m_renderer_event_handler.on_window_resize(width, height)) ||
            (window->m_driver_event_handler.on_window_resize && window->m_driver_event_handler.on_window_resize(width, height));
    });
    glfwSetWindowCloseCallback(m_handle, [](GLFWwindow* handle) {
        Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(handle));
        (window->m_renderer_event_handler.on_window_close && window->m_renderer_event_handler.on_window_close()) ||
            (window->m_driver_event_handler.on_window_close && window->m_driver_event_handler.on_window_close());
    });
}

} // namespace Maki
#endif
