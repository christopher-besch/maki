#include "pch.h"

#include "core/log.h"
#include "open_gl_renderer.h"

namespace Maki {

OpenGLRenderer::OpenGLRenderer()
{
    MAKI_LOG_EXTRA("Creating OpenGL Renderer.");
}

OpenGLRenderer::~OpenGLRenderer()
{
    MAKI_LOG_EXTRA("Destructing OpenGL Renderer.");
}

} // namespace Maki
