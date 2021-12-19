#include "interface.h"

#include "pch.h"

#include "core/log.h"

namespace Maki {

Renderer* init(Renderer::Implementation renderer_impl)
{
    Log::init();
    MAKI_LOG_EXTRA("Initializing.");
    Renderer::set_renderer_api(renderer_impl);
    Renderer* renderer = Renderer::create();
    return renderer;
}

bool shutdown(Renderer* renderer)
{
    MAKI_LOG_EXTRA("Shutting down.");
    delete renderer;
    return true;
}

} // namespace Maki
