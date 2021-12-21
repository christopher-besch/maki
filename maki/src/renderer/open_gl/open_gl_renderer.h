#pragma once

#include "renderer/renderer.h"

namespace Maki {

class OpenGLRenderer: public Renderer {
public:
    OpenGLRenderer(const std::string& title, uint32_t width, uint32_t height);
    ~OpenGLRenderer();

    virtual void end_frame() override;
};

} // namespace Maki
