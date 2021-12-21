#include "pch.h"

#include "core/log.h"
#include "open_gl_renderer.h"

namespace Maki {

OpenGLRenderer::OpenGLRenderer(const std::string& title, uint32_t width, uint32_t height)
    : Renderer(title, width, height)
{
    MAKI_LOG_EXTRA("Creating OpenGL Renderer.");
    MAKI_LOG_EXTRA("Initializing GLEW.");
    glewExperimental = true;
    if(glewInit() != GLEW_OK)
        MAKI_RAISE_CRITICAL("Failed to initialize GLEW.");
}

OpenGLRenderer::~OpenGLRenderer()
{
    MAKI_LOG_EXTRA("Destructing OpenGL Renderer.");
}

} // namespace Maki
