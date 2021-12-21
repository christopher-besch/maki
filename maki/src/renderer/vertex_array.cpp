#include "pch.h"

#include "buffer.h"

#include "renderer/opengl/opengl_vertex_array.h"
#include "renderer/renderer.h"

namespace Maki {

VertexArray* VertexArray::create()
{
    switch(Renderer::get_renderer_api()) {
    case Renderer::Implementation::none:
        MAKI_RAISE_CRITICAL("Renderer::Implementation::none is not supported.");
        return nullptr;
    case Renderer::Implementation::opengl:
        return new OpenGLVertexArray();
    default:
        MAKI_RAISE_CRITICAL("The requested renderer implementation is not supported.");
        return nullptr;
    }
}

} // namespace Maki
