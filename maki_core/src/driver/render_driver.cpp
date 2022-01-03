#include "pch.h"

#include "render_driver.h"

namespace Maki {

RenderDriver::RenderDriver(const std::string& title, uint32_t width, uint32_t height)
{
    m_render_thread = new RenderThread(title, width, height, [this]() { m_terminated = true; });
}

RenderDriver::~RenderDriver()
{
    delete m_render_thread;
}

} // namespace Maki
