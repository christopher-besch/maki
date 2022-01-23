#pragma once

#include "renderer/buffer.h"

namespace Maki {

// bind (multiple) vertex buffers and one index buffer together
class VertexArray {
public:
    static VertexArray* create();

public:
    virtual ~VertexArray() = default;

    // unbind has to be called after vertex array isn't being used anymore -> different vertex buffer creation would spoil this vao
    // use VertexArrayBind unless raw use of bind/unbind completely unavoidable
    virtual void bind() const   = 0;
    virtual void unbind() const = 0;

    virtual void add_vertex_buffer(VertexBuffer* vertex_buffer) = 0;
    virtual void set_index_buffer(IndexBuffer* index_buffer)    = 0;
};

// RAII approach to binding/unbinding a vertex array
class VertexArrayBind {
public:
    VertexArrayBind(const VertexArray* vertex_array)
        : m_vertex_array(vertex_array)
    {
        m_vertex_array->bind();
    }

    ~VertexArrayBind()
    {
        m_vertex_array->unbind();
    }

private:
    const VertexArray* m_vertex_array {nullptr};
};

} // namespace Maki
