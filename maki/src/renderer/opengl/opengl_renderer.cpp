#include "pch.h"

#include "opengl_renderer.h"

#include "core/log.h"
#include "core/stringifier.h"

namespace Maki {

inline void log_gl_extra(const std::string& source, const std::string& type, GLuint id, const std::string& severity, const char* message)
{
    MAKI_LOG_EXTRA("OpenGL Message: Source: {0} Type: {1} ID: {2} Severity: {3}\n{4}",
                   source, type, id, severity, message);
}
inline void log_gl_warn(const std::string& source, const std::string& type, GLuint id, const std::string& severity, const char* message)
{
    MAKI_LOG_WARN("OpenGL Message: Source: {0} Type: {1} ID: {2} Severity: {3}\n{4}",
                  source, type, id, severity, message);
}
inline void log_gl_error(const std::string& source, const std::string& type, GLuint id, const std::string& severity, const char* message)
{
    MAKI_LOG_ERROR("OpenGL Message: Source: {0} Type: {1} ID: {2} Severity: {3}\n{4}",
                   source, type, id, severity, message);
}

OpenGLRenderer::OpenGLRenderer(const std::string& title, uint32_t width, uint32_t height, EventHandler driver_event_handler)
    : Renderer {title, width, height, driver_event_handler}
{
    MAKI_LOG_EXTRA("Creating OpenGL Renderer.");
    MAKI_LOG_EXTRA("Initializing GLEW.");
    glewExperimental = true;
    if(glewInit() != GLEW_OK)
        MAKI_RAISE_CRITICAL("Failed to initialize GLEW.");

#ifndef NDEBUG
    glDebugMessageCallback([](GLenum source, GLenum type, uint32_t id, GLenum severity, GLsizei, const char* message, const void*) {
        std::string source_str   = Stringifier::gl_msg_source(source);
        std::string type_str     = Stringifier::gl_msg_type(type);
        std::string severity_str = Stringifier::gl_msg_severity(severity);

        switch(severity) {
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            log_gl_extra(source_str, type_str, id, severity_str, message);
            break;
        case GL_DEBUG_SEVERITY_LOW:
            log_gl_extra(source_str, type_str, id, severity_str, message);
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            log_gl_warn(source_str, type_str, id, severity_str, message);
            break;
        case GL_DEBUG_SEVERITY_HIGH:
            log_gl_error(source_str, type_str, id, severity_str, message);
            break;
        default:
            log_gl_error(source_str, type_str, id, severity_str, message);
            break;
        }
    },
                           nullptr);
#endif
    set_clear_col({0.0f, 0.0f, 0.4f, 1.0f});
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glDepthFunc(GL_LESS);
}

OpenGLRenderer::~OpenGLRenderer()
{
    MAKI_LOG_EXTRA("Destructing OpenGL Renderer.");
}

void OpenGLRenderer::set_clear_col(vec4 color)
{
    glClearColor(color.r, color.g, color.b, color.a);
}

void OpenGLRenderer::draw(VertexArray* vertex_array, IndexBuffer* index_buffer, Shader* shader)
{
    shader->bind();
    vertex_array->bind();
    index_buffer->bind();

    glDrawElements(GL_TRIANGLES, index_buffer->get_count(), GL_UNSIGNED_INT, nullptr);
}

void OpenGLRenderer::start_frame()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderer::set_viewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
    glViewport(x, y, width, height);
}

} // namespace Maki
