#pragma once

#include "../buffer.h"

namespace Maki {

class OpenGLVertexBuffer: public VertexBuffer {
public:
    // dynamic
    OpenGLVertexBuffer(const std::initializer_list<BufferElement>& elements, size_t size);
    // static
    OpenGLVertexBuffer(const std::initializer_list<BufferElement>& elements, const void* data, size_t size);

    ~OpenGLVertexBuffer();

    virtual void set_data(const void* data, size_t size) override;

    virtual void bind() const override;
    virtual void unbind() const override;

private:
    uint32_t m_id;
};

class OpenGLIndexBuffer: public IndexBuffer {
public:
    OpenGLIndexBuffer(uint32_t count, const uint32_t* indices);
    ~OpenGLIndexBuffer();

    virtual void bind() const override;
    virtual void unbind() const override;

    virtual uint32_t get_count() const override { return m_count; };

private:
    uint32_t m_id;
    uint32_t m_count;
};

} // namespace Maki
