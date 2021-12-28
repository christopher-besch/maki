#pragma once

#include "driver/camera_driver.h"
#include "renderer/renderer.h"

namespace Maki {

class RenderDriver {
public:
    RenderDriver(const std::string& title, uint32_t width, uint32_t height)
        : m_renderer {Renderer::create(title, width, height)}, m_camera_driver {new CameraDriver(m_renderer)}
    {
    }

    ~RenderDriver()
    {
        delete m_renderer;
    }

    void run();

private:
    Renderer*     m_renderer;
    CameraDriver* m_camera_driver;
};

} // namespace Maki
