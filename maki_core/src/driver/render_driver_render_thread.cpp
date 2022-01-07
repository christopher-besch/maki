#include "pch.h"

#include "render_driver.h"

namespace Maki {

void RenderDriver::render_thread_func(const std::string& title, uint32_t width, uint32_t height)
{
    setup(title, width, height);
    run();
    m_terminated = true;
}

void RenderDriver::setup(const std::string& title, uint32_t width, uint32_t height)
{
    // setup can't be performed twice at the same time
    lock lock {s_setup_mutex};
    m_renderer      = Renderer::create(title, width, height);
    m_camera_driver = new CameraDriver(m_renderer);
}

void RenderDriver::run()
{
    do {
        sync_frame_target();
        render_frame();
    } while(!m_renderer->should_terminate());
}

void RenderDriver::render_frame()
{
    // TODO: remove example
    m_camera_driver->update(m_renderer->get_last_frame_time());
    m_renderer->start_frame();
    // m_renderer->get_camera()->set_fov(glm::radians(float(i)));
    mat4 mvp = m_renderer->get_camera()->get_view_projection() * mat4 {1.0f};
    m_shader->set_mat4("u_mvp", mvp);
    m_renderer->draw(m_vertex_array, m_index_buffer, m_shader);
    m_renderer->end_frame();
}

void RenderDriver::sync_frame_target()
{
    chrono_sync();
    m_render_cuboid_chain.set_frame(m_target_frame, m_cuboid_diff_lifetime);
}
void RenderDriver::chrono_sync()
{
    if(m_cuboid_diff_lifetime.get_first_outdated_frame() <= m_render_cuboid_chain.get_frame())
        m_render_cuboid_chain.chrono_sync();
}

} // namespace Maki
