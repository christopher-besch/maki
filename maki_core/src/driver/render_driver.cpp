#include "pch.h"

#include "driver/camera_driver.h"
#include "render_driver.h"
#include "renderer/shader.h"

namespace Maki {

void RenderDriver::run()
{
    // TODO: remove example
    Shader* shader = Shader::create("maki_core/res/shaders/simple_vertex.glsl", "maki_core/res/shaders/simple_fragment.glsl");
    shader->set_float3("u_color", {1.0f, 1.0f, 0.0f});

    // cube vertices
    const GLfloat vertex_buffer_data[] = {
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,

        1.0f, 1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,

        1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,

        1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f,

        1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,

        -1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,

        1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, 1.0f, -1.0f,

        1.0f, -1.0f, -1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,

        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,

        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, 1.0f,

        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f};
    VertexBuffer* vertex_buffer = VertexBuffer::create({{"a_position", DataType::float3}}, vertex_buffer_data, sizeof(vertex_buffer_data));

    uint32_t index_buffer_data[12 * 3];
    for(uint32_t i {0}; i < 12 * 3; ++i)
        index_buffer_data[i] = i;

    IndexBuffer* index_buffer = IndexBuffer::create(48 * 3, index_buffer_data);

    VertexArray* vertex_array = VertexArray::create();
    vertex_array->add_vertex_buffer(vertex_buffer);
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
    delete vertex_buffer;
    delete vertex_array;
}

} // namespace Maki
