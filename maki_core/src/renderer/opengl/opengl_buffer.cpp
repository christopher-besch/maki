#include "pch.h"

#include "opengl_buffer.h"

namespace Maki {

// VertexBuffer
OpenGLVertexBuffer::OpenGLVertexBuffer(const std::initializer_list<BufferElement>& elements, size_t size)
    : VertexBuffer(elements, true)
{
    glCreateBuffers(1, &m_id);
    bind();
    // GL_ARRAY_BUFFER allows data loading regardless of vao state
    glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

OpenGLVertexBuffer::OpenGLVertexBuffer(const std::initializer_list<BufferElement>& elements, const void* data, size_t size)
    : VertexBuffer(elements, false)
{
    glCreateBuffers(1, &m_id);
    bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
    glDeleteBuffers(1, &m_id);
}

void OpenGLVertexBuffer::set_data(const void* data, size_t size)
{
    MAKI_ASSERT_CRITICAL(m_dynamic, "OpenGLVertexBuffer::set_data can't be used with a static buffer.");
    bind();
    // replace everything
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

void OpenGLVertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
}
void OpenGLVertexBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// IndexBuffer
OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t count, const uint32_t* indices)
    : m_count(count)
{
    glCreateBuffers(1, &m_id);
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
    glDeleteBuffers(1, &m_id);
}

void OpenGLIndexBuffer::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}
void OpenGLIndexBuffer::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

} // namespace Maki
