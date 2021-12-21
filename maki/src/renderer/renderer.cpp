#include "pch.h"

#include "renderer.h"

#include "core/log.h"
#include "open_gl/opengl_renderer.h"

namespace Maki {

Renderer* Renderer::create(const std::string& title, uint32_t width, uint32_t height)
{
    switch(s_renderer_impl) {
    case Implementation::none:
        MAKI_RAISE_CRITICAL("Renderer::Implementation::none is not supported.");
        return nullptr;
    case Implementation::open_gl:
        return new OpenGLRenderer(title, width, height);
    default:
        MAKI_RAISE_CRITICAL("The requested renderer implementation is not supported.");
        return nullptr;
    }
}

} // namespace Maki
