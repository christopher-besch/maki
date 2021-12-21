// designed to be easily marshalled to python
#pragma once

#include "renderer/renderer.h"

namespace Maki {

// return nullptr at failure
Renderer* init(Renderer::Implementation renderer_impl, const std::string& title, uint32_t width, uint32_t height);

// return false at failure
bool shutdown(Renderer* renderer);

} // namespace Maki
