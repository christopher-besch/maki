#include "pch.h"

#include "opengl_renderer.h"

#include "core/log.h"
#include "core/stringifier.h"

namespace Maki {

OpenGLRenderer::OpenGLRenderer(const std::string& title, uint32_t width, uint32_t height)
    : Renderer(title, width, height)
{
    MAKI_LOG_EXTRA("Creating OpenGL Renderer.");
    MAKI_LOG_EXTRA("Initializing GLEW.");
    glewExperimental = true;
    if(glewInit() != GLEW_OK)
        MAKI_RAISE_CRITICAL("Failed to initialize GLEW.");

#ifndef NDEBUG
    glDebugMessageCallback([](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei, const GLchar* message, const void*) {
        MAKI_LOG_ERROR("Message from OpenGL: Source: {0} Type: {1} ID: {2} Severity: {3}\n{4}",
                       Stringifier::gl_msg_source(source),
                       Stringifier::gl_msg_type(type),
                       id,
                       Stringifier::gl_msg_severity(severity),
                       message);
    },
                           nullptr);
#endif
}

OpenGLRenderer::~OpenGLRenderer()
{
    MAKI_LOG_EXTRA("Destructing OpenGL Renderer.");
}

void OpenGLRenderer::draw(VertexArray* vertex_array, IndexBuffer* index_buffer, Shader* shader)
{
    shader->bind();
    vertex_array->bind();
    index_buffer->bind();

    glDrawElements(GL_TRIANGLES, index_buffer->get_count(), GL_UNSIGNED_INT, nullptr);
}

void OpenGLRenderer::end_frame()
{
    m_window->update();
}

} // namespace Maki
