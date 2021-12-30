#include "pch.h"

#include "driver/camera_driver.h"
#include "render_driver.h"
#include "renderer/shader.h"

namespace Maki {

void RenderDriver::run()
{
    // TODO: remove example
    Shader* shader = Shader::create("maki_core/res/shaders/simple_vertex.glsl", "maki_core/res/shaders/simple_fragment.glsl");
    // shader->set_float3("u_color", {1.0f, 1.0f, 0.0f});

    // cube vertices
    const GLfloat vertex_pos[] = {
        -1.0f, -1.0f, +1.0f, // 0 bottom front left
        +1.0f, -1.0f, +1.0f, // 1 bottom front right
        -1.0f, -1.0f, -1.0f, // 2 bottom back  left
        +1.0f, -1.0f, -1.0f, // 3 bottom back  right
        -1.0f, +1.0f, +1.0f, // 4 top    front left
        +1.0f, +1.0f, +1.0f, // 5 top    front right
        -1.0f, +1.0f, -1.0f, // 6 top    back  left
        +1.0f, +1.0f, -1.0f  // 7 top    back  right
    };
    const GLfloat vertex_color[] = {
        0.6f, 0.6f, 0.0f,
        0.0f, 0.0f, 0.6f,
        0.0f, 0.6f, 0.0f,
        0.6f, 0.0f, 0.0f,
        0.0f, 0.6f, 0.0f,
        0.6f, 0.0f, 0.6f,
        0.6f, 0.6f, 0.0f,
        1.0f, 1.0f, 1.0f};
    VertexBuffer* vertex_pos_buffer   = VertexBuffer::create({{"a_position", DataType::float3}}, vertex_pos, sizeof(vertex_pos));
    VertexBuffer* vertex_color_buffer = VertexBuffer::create({{"a_color", DataType::float3}}, vertex_color, sizeof(vertex_color));

    const uint32_t index_buffer_data[] = {
        2, 3, 0, 0, 3, 1, // bottom
        0, 1, 5, 5, 4, 0, // front
        2, 0, 4, 4, 6, 2, // left
        1, 3, 7, 7, 5, 1, // right
        3, 2, 6, 6, 7, 3, // back
        7, 6, 4, 4, 5, 7  // top
    };

    IndexBuffer* index_buffer = IndexBuffer::create(sizeof(index_buffer_data) / sizeof(uint32_t), index_buffer_data);

    VertexArray* vertex_array = VertexArray::create();
    vertex_array->add_vertex_buffer(vertex_pos_buffer);
    vertex_array->add_vertex_buffer(vertex_color_buffer);
    vertex_array->set_index_buffer(index_buffer);

    do {
        m_camera_driver->update(m_renderer->get_last_frame_time());
        m_renderer->start_frame();
        // m_renderer->get_camera()->set_fov(glm::radians(float(i)));
        mat4 mvp = m_renderer->get_camera()->get_view_projection() * mat4 {1.0f};
        shader->set_mat4("u_mvp", mvp);
        m_renderer->draw(vertex_array, index_buffer, shader);
        m_renderer->end_frame();
    } while(!m_renderer->should_terminate());

    delete shader;
    delete vertex_pos_buffer;
    delete vertex_array;
}

} // namespace Maki
