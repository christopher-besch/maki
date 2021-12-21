#pragma once

#include "core/log.h"
#include <GLFW/glfw3.h>
#include <iostream>

namespace Maki {

class Window {
public:
    Window(const std::string& title, uint32_t width, uint32_t height);
    ~Window();

    void create();
    // init performed at creationg of first window
    void init();

private:
    static int s_window_count;

    std::string m_title;
    uint32_t    m_width, m_height;

#if PROJECT == glfw
    GLFWwindow* m_window;
#endif
};

} // namespace Maki
