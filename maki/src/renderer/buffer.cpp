#include "pch.h"

#include "buffer.h"

#include "renderer/opengl/opengl_buffer.h"
#include "renderer/renderer.h"

namespace Maki {

VertexBuffer* VertexBuffer::create(const std::initializer_list<BufferElement>& elements, size_t size)
{
    switch(Renderer::get_renderer_api()) {
    case Renderer::Implementation::none:
        MAKI_RAISE_CRITICAL("Renderer::Implementation::none is not supported.");
        return nullptr;
    case Renderer::Implementation::opengl:
        return new OpenGLVertexBuffer(elements, size);
    default:
        MAKI_RAISE_CRITICAL("The requested renderer implementation is not supported.");
        return nullptr;
    }
}

VertexBuffer* VertexBuffer::create(const std::initializer_list<BufferElement>& elements, const void* data, size_t size)
{
    switch(Renderer::get_renderer_api()) {
    case Renderer::Implementation::none:
        MAKI_RAISE_CRITICAL("Renderer::Implementation::none is not supported.");
        return nullptr;
    case Renderer::Implementation::opengl:
        return new OpenGLVertexBuffer(elements, data, size);
    default:
        MAKI_RAISE_CRITICAL("The requested renderer implementation is not supported.");
        return nullptr;
    }
}

IndexBuffer* IndexBuffer::create(uint32_t count, uint32_t* indices)
{
    switch(Renderer::get_renderer_api()) {
    case Renderer::Implementation::none:
        MAKI_RAISE_CRITICAL("Renderer::Implementation::none is not supported.");
        return nullptr;
    case Renderer::Implementation::opengl:
        return new OpenGLIndexBuffer(count, indices);
    default:
        MAKI_RAISE_CRITICAL("The requested renderer implementation is not supported.");
        return nullptr;
    }
}

} // namespace Maki
