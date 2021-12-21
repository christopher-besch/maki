#pragma once

#include "renderer/renderer.h"

namespace Maki {

class RenderDriver {
public:
    RenderDriver(const std::string& title, uint32_t width, uint32_t height)
        : m_renderer(Renderer::create(title, width, height)) {}

    ~RenderDriver()
    {
        delete m_renderer;
    }

    void run();

private:
    Renderer* m_renderer;
};

} // namespace Maki
