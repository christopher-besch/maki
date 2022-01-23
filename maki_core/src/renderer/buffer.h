#pragma once

#include "core/log.h"
#include "renderer/types.h"

namespace Maki {

// one variable type in a buffer
// a buffer can have multiple BufferElements
struct BufferElement {
    std::string name;
    DataType    type;
    size_t      size;
    bool        normalized;
    // to be calculated in VertexBuffer::calculate_offset_and_stride
    uint32_t offset {0};

    BufferElement() = default;
    BufferElement(const std::string& name, DataType type, bool normalized = false)
        : name {name}, type {type}, size {data_type_size(type)}, normalized {normalized} {}
};

// pass data to GPU, BufferElements define how that data looks like
class VertexBuffer {
public:
    // dynamic
    static VertexBuffer* create(const std::initializer_list<BufferElement>& elements, size_t size);
    // static
    static VertexBuffer* create(const std::initializer_list<BufferElement>& elements, const void* data, size_t size);

public:
    VertexBuffer(const std::initializer_list<BufferElement>& elements, bool dynamic)
        : m_elements {elements}, m_dynamic {dynamic}
    {
        calculate_offset_and_stride();
    }

    virtual ~VertexBuffer() = default;

    // can only be used when not static
    // WARN: correct vao has to be bound prior to use
    virtual void set_data(const void* data, size_t size) = 0;

    virtual void bind() const   = 0;
    virtual void unbind() const = 0;

    const std::vector<BufferElement>& get_elements() { return m_elements; }
    uint32_t                          get_stride() { return m_stride; }

protected:
    void calculate_offset_and_stride()
    {
        size_t offset {0};
        m_stride = 0;
        for(BufferElement& element: m_elements) {
            element.offset = offset;
            offset += element.size;
            m_stride += element.size;
        }
    }

protected:
    std::vector<BufferElement> m_elements;
    uint32_t                   m_stride {0};
    // true -> data can be updated
    // false -> data has to be set at creation
    bool m_dynamic;
};

// what vertices should be rendered in what order
class IndexBuffer {
public:
    static IndexBuffer* create(uint32_t count, const uint32_t* indices);

public:
    virtual ~IndexBuffer() = default;

    virtual void bind() const   = 0;
    virtual void unbind() const = 0;

    virtual uint32_t get_count() const = 0;
};

} // namespace Maki
