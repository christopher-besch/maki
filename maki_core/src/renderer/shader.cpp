#include "pch.h"

#include "buffer.h"

#include "renderer/opengl/opengl_shader.h"
#include "renderer/renderer.h"

namespace Maki {

Shader* Shader::create(const std::string& vert_path, const std::string& frag_path)
{
    switch(Renderer::get_renderer_impl()) {
    case Renderer::Implementation::none:
        MAKI_RAISE_CRITICAL("Renderer::Implementation::none is not supported.");
        return nullptr;
    case Renderer::Implementation::opengl:
        return new OpenGLShader(vert_path, frag_path);
    default:
        MAKI_RAISE_CRITICAL("The requested renderer implementation is not supported.");
        return nullptr;
    }
}

} // namespace Maki
