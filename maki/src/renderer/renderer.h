#pragma once

#include "pch.h"

namespace Maki {

class Renderer {
public:
    enum class Implementation {
        none    = 0,
        open_gl = 1
    };

public:
    virtual ~Renderer() = default;

    static Implementation get_renderer_api() { return s_renderer_impl; }
    static void           set_renderer_api(Implementation renderer_impl) { s_renderer_impl = renderer_impl; }

    // create renderer with implementation specified in s_renderer_impl
    // every implementation-specific class uses this concept
    static Renderer* create();

private:
    static Implementation s_renderer_impl;
};

} // namespace Maki
