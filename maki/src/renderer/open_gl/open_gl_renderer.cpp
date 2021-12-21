#include "pch.h"

#include "core/log.h"
#include "open_gl_renderer.h"

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
        MAKI_LOG_ERROR("Message from OpenGL:\nSource: {0}\nType: {1}\nID: {2}\nSeverity: {3}\n\n{4}", source, type, id, severity, message);
    },
                           nullptr);
#endif
}

OpenGLRenderer::~OpenGLRenderer()
{
    MAKI_LOG_EXTRA("Destructing OpenGL Renderer.");
}

void OpengGLRenderer::draw(VertexArray* vertex_array, IndexBuffer* index_buffer, Shader* shader)
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
