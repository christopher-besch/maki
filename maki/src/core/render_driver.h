#pragma once

#include "renderer/renderer.h"

namespace Maki {

class RenderDriver {
public:
    RenderDriver(const std::string& title, uint32_t width, uint32_t height)
        // TODO: set correct EventHandler
        : m_renderer(Renderer::create(title, width, height, EventHandler {}))
    {
    }

    ~RenderDriver()
    {
        delete m_renderer;
    }

    void run();

private:
    Renderer* m_renderer;
};

} // namespace Maki
