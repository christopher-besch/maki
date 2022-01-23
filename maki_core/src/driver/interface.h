#pragma once

#include "core/log.h"
#include "core/thread_safety.h"
#include "renderer/renderer.h"

namespace Maki {

// any client-facing functions outside of RenderDriver
inline void init(Renderer::Implementation renderer_impl)
{
    SET_THREAD_TYPE_CONTROL();
    Log::init();
    Renderer::set_renderer_impl(renderer_impl);
}

} // namespace Maki
