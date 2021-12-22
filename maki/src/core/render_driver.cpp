#include "pch.h"

#include "render_driver.h"
#include "renderer/shader.h"

namespace Maki {

void RenderDriver::run()
{
    // TODO: remove example
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glDepthFunc(GL_LESS);

    Shader* shader = Shader::create("maki/res/shaders/simple_vertex.glsl", "maki/res/shaders/simple_fragment.glsl");

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

    do {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        m_renderer->draw(vertex_array, index_buffer, shader);
        m_renderer->end_frame();
    } while(!m_renderer->should_terminate());

    delete shader;
    delete vertex_buffer;
    delete vertex_array;
}

} // namespace Maki
