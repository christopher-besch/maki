#include "pch.h"

#include "interface.h"

#include "core/log.h"

namespace Maki {

RenderDriver* init(Renderer::Implementation renderer_impl, const std::string& title, uint32_t width, uint32_t height)
{
    Log::init();
    MAKI_LOG_EXTRA("Initializing.");
    Renderer::set_renderer_api(renderer_impl);
    RenderDriver* render_driver = new RenderDriver(title, width, height);
    render_driver->run();
    return render_driver;
}

void shutdown(RenderDriver* render_driver)
{
    MAKI_LOG_EXTRA("Shutting down.");
    delete render_driver;
}

} // namespace Maki
