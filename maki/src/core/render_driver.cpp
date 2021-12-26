#include "pch.h"

#include "render_driver.h"
#include "renderer/shader.h"

namespace Maki {

void RenderDriver::run()
{
    // TODO: remove example
    Shader* shader = Shader::create("maki/res/shaders/simple_vertex.glsl", "maki/res/shaders/simple_fragment.glsl");
    shader->set_float3("u_color", {1.0f, 1.0f, 0.0f});

    const float vertex_buffer_data[] = {
        -1.0f,
        -1.0f,
        0.0f,

        1.0f,
        -1.0f,
        0.0f,

        0.0f,
        1.0f,
        0.0f,
    };
    VertexBuffer* vertex_buffer = VertexBuffer::create({{"a_position", DataType::float3}}, vertex_buffer_data, sizeof(vertex_buffer_data));

    const uint32_t index_buffer_data[] = {0, 1, 2};
    IndexBuffer*   index_buffer        = IndexBuffer::create(3, index_buffer_data);

    VertexArray* vertex_array = VertexArray::create();
    vertex_array->add_vertex_buffer(vertex_buffer);
    vertex_array->set_index_buffer(index_buffer);

    int   i {1};
    float x {0.0f};
    do {
        m_renderer->start_frame();
        m_renderer->get_camera()->set_fov(glm::radians(float(i)));
        MAKI_LOG_WARN("fov: {} degrees", i);
        mat4 mvp = m_renderer->get_camera()->get_view_projection() * mat4 {1.0f};
        shader->set_mat4("u_mvp", mvp);
        shader->set_float3("u_color", {1.0f, x, 0.0f});
        m_renderer->draw(vertex_array, index_buffer, shader);
        m_renderer->end_frame();
        i += 10;
        x += 0.1f;
        x = fmod(x, 1.0f);
    } while(!m_renderer->should_terminate());

    delete shader;
    delete vertex_buffer;
    delete vertex_array;
}

} // namespace Maki
