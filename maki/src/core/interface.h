// designed to be easily marshalled to python
#pragma once

#include "pch.h"
#include "renderer/renderer.h"

namespace Maki {

// return nullptr at failure
Renderer* init(Renderer::Implementation renderer_impl);

// return false at failure
bool shutdown(Renderer* renderer);

} // namespace Maki
