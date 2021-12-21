#if PROJECT == glfw
#include "pch.h"

#include "../window.h"
#include "core/log.h"
#include "renderer/renderer.h"

namespace Maki {

Window::~Window()
{
    glfwDestroyWindow(m_window);
    --s_window_count;
    if(s_window_count == 0)
        glfwTerminate();
}

void Window::create()
{
    MAKI_LOG_EXTRA("Creating GLFW window '{0}' ({1}, {2}).", m_title, m_width, m_height);

    // 4x antialiasing
    glfwWindowHint(GLFW_SAMPLES, 4);
    // TODO: differentiate between OpenGL and Vulkan
    // OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // for macos
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    // disable old OpenGL
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
    ++s_window_count;
    if(m_window == nullptr)
        MAKI_RAISE_CRITICAL("Failed to create GLFW window.");
    glfwMakeContextCurrent(m_window);
}

void Window::init()
{
    MAKI_LOG_EXTRA("Initializing GLFW.");

    int success = glfwInit();
    MAKI_ASSERT(success, "Couldn't initialize GLFW.");
    glfwSetErrorCallback([](int error, const char* description) {
        MAKI_LOG_ERROR("GLFW Error ({0}): {1}", error, description);
    });

#ifdef NDEBUG
    if(Renderer::get_renderer_api() == Renderer::Implementation::open_gl)
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif
}

void Window::update()
{
    glfwSwapBuffers(m_window);
    glfwPollEvents();
}

bool Window::should_close()
{
    // TODO: move escape key to better location
    return glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(m_window);
}

} // namespace Maki
#endif
