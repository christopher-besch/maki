// designed to be easily marshalled to python
#pragma once

#include "core/render_driver.h"

namespace Maki {

// return nullptr at failure
RenderDriver* init(Renderer::Implementation renderer_impl, const std::string& title, uint32_t width, uint32_t height);

void shutdown(RenderDriver* render_driver);

} // namespace Maki
