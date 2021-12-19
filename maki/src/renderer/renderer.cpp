#include "pch.h"

#include "core/log.h"
#include "open_gl/open_gl_renderer.h"
#include "renderer.h"

namespace Maki {

Renderer::Implementation Renderer::s_renderer_impl = Renderer::Implementation::none;

Renderer* Renderer::create()
{
    switch(s_renderer_impl) {
    case Implementation::none:
        MAKI_RAISE_CRITICAL("Renderer::Implementation::none is not supported.");
        return nullptr;
    case Implementation::open_gl:
        return new OpenGLRenderer();
    default:
        MAKI_RAISE_CRITICAL("The requested renderer implementation is not supported.");
        return nullptr;
    }
}

} // namespace Maki
