#include "pch.h"

#include "opengl_vertex_array.h"
#include "renderer/opengl/opengl_types.h"

namespace Maki {

OpenGLVertexArray::OpenGLVertexArray()
{
    glCreateVertexArrays(1, &m_id);
}
OpenGLVertexArray::~OpenGLVertexArray()
{
    glDeleteVertexArrays(1, &m_id);
}

void OpenGLVertexArray::bind() const
{
    glBindVertexArray(m_id);
}
void OpenGLVertexArray::unbind() const
{
    glBindVertexArray(0);
}

void OpenGLVertexArray::add_vertex_buffer(VertexBuffer* vertex_buffer)
{
    bind();
    vertex_buffer->bind();

    for(const BufferElement& element: vertex_buffer->get_elements()) {
        glEnableVertexAttribArray(m_next_attrib_id);
        glVertexAttribPointer(
            m_next_attrib_id,
            data_type_components(element.type),
            data_type_to_gl_enum(element.type),
            element.normalized ? GL_TRUE : GL_FALSE,
            vertex_buffer->get_stride(),
            reinterpret_cast<const void*>(element.offset));
        ++m_next_attrib_id;
    }
    m_vertex_buffers.push_back(vertex_buffer);
}

void OpenGLVertexArray::set_index_buffer(IndexBuffer* index_buffer)
{
    bind();
    index_buffer->bind();
    m_index_buffer = index_buffer;
}

} // namespace Maki
