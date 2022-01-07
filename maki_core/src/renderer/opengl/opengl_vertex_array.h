#pragma once

#include "../vertex_array.h"

namespace Maki {

class OpenGLVertexArray: public VertexArray {
public:
    OpenGLVertexArray();
    ~OpenGLVertexArray();

    virtual void bind() const override;
    virtual void unbind() const override;

    virtual void add_vertex_buffer(VertexBuffer* vertex_buffer) override;
    virtual void set_index_buffer(IndexBuffer* index_buffer) override;

private:
    uint32_t                   m_id;
    uint32_t                   m_next_attrib_id {0};
    std::vector<VertexBuffer*> m_vertex_buffers;
    IndexBuffer*               m_index_buffer {nullptr};
};

} // namespace Maki
