#include "buffer.h"

#include "renderer/renderer.h"

namespace Maki {

VertexArray* VertexArray::create()
{
    switch(Renderer::get_renderer_api()) {
    case Renderer::Implementation::none:
        MAKI_RAISE_CRITICAL("Renderer::Implementation::none is not supported.");
        return nullptr;
    case Renderer::Implementation::open_gl:
        return new OpenGLVertexArray();
    default:
        MAKI_RAISE_CRITICAL("The requested renderer implementation is not supported.");
        return nullptr;
    }
}

} // namespace Maki
