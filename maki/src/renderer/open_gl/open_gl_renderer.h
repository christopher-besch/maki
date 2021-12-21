#pragma once

#include "renderer/renderer.h"

namespace Maki {

class OpenGLRenderer: public Renderer {
public:
    OpenGLRenderer(const std::string& title, uint32_t width, uint32_t height);
    ~OpenGLRenderer();
};

} // namespace Maki
