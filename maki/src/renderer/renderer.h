#pragma once

#include "platform/window.h"

namespace Maki {

class Renderer {
public:
    enum class Implementation {
        none    = 0,
        open_gl = 1
    };

public:
    Renderer(const std::string& title, uint32_t width, uint32_t height)
        : m_window(new Window(title, width, height)) {}
    virtual ~Renderer()
    {
        delete m_window;
    }

    static Implementation get_renderer_api() { return s_renderer_impl; }
    static void           set_renderer_api(Implementation renderer_impl) { s_renderer_impl = renderer_impl; }

    // create renderer with implementation specified in s_renderer_impl
    // every implementation-specific class uses this concept
    static Renderer* create(const std::string& title, uint32_t width, uint32_t height);

private:
    static Implementation s_renderer_impl;

private:
    Window* m_window;
};

} // namespace Maki
