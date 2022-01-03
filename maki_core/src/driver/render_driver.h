#pragma once

#include <thread>

#include "driver/render_thread.h"

namespace Maki {

class RenderDriver {
public:
    RenderDriver(const std::string& title, uint32_t width, uint32_t height);

    ~RenderDriver();

    void await_termination() { m_render_thread->await_termination(); };
    bool is_terminated() { return m_terminated; }

private:
    RenderThread* m_render_thread;
    bool          m_terminated {false};
};

} // namespace Maki
