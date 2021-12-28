#pragma once

#include "core/log.h"
#include "renderer/renderer.h"

namespace Maki {

inline void init(Renderer::Implementation renderer_impl)
{
    Log::init();
    Renderer::set_renderer_impl(renderer_impl);
}

} // namespace Maki
