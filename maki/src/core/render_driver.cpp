#include "pch.h"

#include "render_driver.h"

namespace Maki {

void RenderDriver::run()
{
    do {
        m_renderer->end_frame();
    } while(!m_renderer->should_terminate());
}

} // namespace Maki
