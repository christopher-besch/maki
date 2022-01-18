#pragma once

#include "renderer/buffer.h"

namespace Maki {

// bind (multiple) vertex buffers and one index buffer together
class VertexArray {
public:
    static VertexArray* create();

public:
    virtual ~VertexArray() = default;

    virtual void bind() const   = 0;
    virtual void unbind() const = 0;

    virtual void add_vertex_buffer(VertexBuffer* vertex_buffer) = 0;
    virtual void set_index_buffer(IndexBuffer* index_buffer)    = 0;
};

} // namespace Maki
