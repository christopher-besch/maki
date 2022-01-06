#include "pch.h"

#include "render_driver.h"

namespace Maki {

std::mutex RenderDriver::s_setup_mutex;

// called from control thread //
RenderDriver::RenderDriver(const std::string& title, uint32_t width, uint32_t height)
{
    m_render_thread = std::thread([this, title, width, height]() {
        // setup can't be performed twice at the same time
        s_setup_mutex.lock();
        m_renderer      = Renderer::create(title, width, height);
        m_camera_driver = new CameraDriver(m_renderer);

        setup();
        s_setup_mutex.unlock();
        run();
        m_terminated = true;
    });
}

RenderDriver::~RenderDriver()
{
    MAKI_ASSERT_WARN(m_render_thread.joinable(), "Attempting termination of unjoinable render thread.");
    m_renderer->terminate();
    await_termination();

    delete m_renderer;
    delete m_camera_driver;

    // TODO: remove example
    delete m_shader;
    delete m_vertex_pos_buffer;
    delete m_vertex_col_buffer;
    delete m_vertex_array;
    delete m_index_buffer;
}

void RenderDriver::await_termination()
{
    // not even running?
    if(!m_render_thread.joinable())
        return;
    m_render_thread.join();
}

uint32_t RenderDriver::add_cuboid_atom()
{
    m_control_cuboid_chain.add();
    return m_control_cuboid_chain.size() - 1;
}
void RenderDriver::show_cuboid_atom(uint32_t id, uint32_t frame, bool render)
{
    MAKI_ASSERT_CRITICAL(m_control_cuboid_chain.size() > id, "ID {} for CuboidAtoms hasn't been allocated yet.", id);
    MAKI_ASSERT_CRITICAL(frame < 1, "Frame {} is invalid.", frame);
    while(frame >= m_cuboid_diffs.size())
        m_cuboid_diffs.emplace_back();

    set_control_frame(frame - 1);

    if(m_control_cuboid_chain[id].render != render)
        m_cuboid_diffs[frame].add(new ToggleRenderDiff<CuboidAtom>());
}
void RenderDriver::translate_cuboid_atom(uint32_t id, uint32_t frame, vec3 delta)
{
}

void RenderDriver::set_control_frame(uint32_t frame)
{
    m_control_cuboid_chain.set_frame(frame, m_cuboid_diffs);
}

// called from render thread //
void RenderDriver::setup()
{
    // TODO: remove example
    m_shader = Shader::create("maki_core/res/shaders/simple_vertex.glsl", "maki_core/res/shaders/simple_fragment.glsl");
    // shader->set_float3("u_color", {1.0f, 1.0f, 0.0f});

    // cube vertices
    const float vertex_pos[] = {
        -1.0f, -1.0f, +1.0f, // 0 bottom front left
        +1.0f, -1.0f, +1.0f, // 1 bottom front right
        -1.0f, -1.0f, -1.0f, // 2 bottom back  left
        +1.0f, -1.0f, -1.0f, // 3 bottom back  right
        -1.0f, +1.0f, +1.0f, // 4 top    front left
        +1.0f, +1.0f, +1.0f, // 5 top    front right
        -1.0f, +1.0f, -1.0f, // 6 top    back  left
        +1.0f, +1.0f, -1.0f  // 7 top    back  right
    };
    const float vertex_color[] = {
        0.6f, 0.6f, 0.0f,
        0.0f, 0.0f, 0.6f,
        0.0f, 0.6f, 0.0f,
        0.6f, 0.0f, 0.0f,
        0.0f, 0.6f, 0.0f,
        0.6f, 0.0f, 0.6f,
        0.6f, 0.6f, 0.0f,
        1.0f, 1.0f, 1.0f};
    m_vertex_pos_buffer = VertexBuffer::create({{"a_position", DataType::float3}}, vertex_pos, sizeof(vertex_pos));
    m_vertex_col_buffer = VertexBuffer::create({{"a_color", DataType::float3}}, vertex_color, sizeof(vertex_color));

    const uint32_t index_buffer_data[] = {
        2, 3, 0, 0, 3, 1, // bottom
        0, 1, 5, 5, 4, 0, // front
        2, 0, 4, 4, 6, 2, // left
        1, 3, 7, 7, 5, 1, // right
        3, 2, 6, 6, 7, 3, // back
        7, 6, 4, 4, 5, 7  // top
    };

    m_index_buffer = IndexBuffer::create(sizeof(index_buffer_data) / sizeof(uint32_t), index_buffer_data);

    m_vertex_array = VertexArray::create();
    m_vertex_array->add_vertex_buffer(m_vertex_pos_buffer);
    m_vertex_array->add_vertex_buffer(m_vertex_col_buffer);
    m_vertex_array->set_index_buffer(m_index_buffer);
}

void RenderDriver::run()
{
    do {
        render_frame();
    } while(!m_renderer->should_terminate());
    // thread killed
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

} // namespace Maki
