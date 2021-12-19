#pragma once

#include "pch.h"

#include "renderer/renderer.h"

namespace Maki {

class OpenGLRenderer: public Renderer {
public:
    OpenGLRenderer();
    ~OpenGLRenderer();
};

} // namespace Maki
