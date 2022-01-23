#include "pch.h"

#include "batch_renderer.h"

namespace Maki {

BatchRenderer::BatchRenderer(Renderer* renderer, VertexBuffer* vertex_buffer, IndexBuffer* index_buffer, Shader* shader)
    : m_renderer {renderer},
      m_vertex_array {VertexArray::create()},
      m_vertex_buffer {vertex_buffer},
      m_index_buffer {index_buffer},
      m_shader {shader}
{
    m_vertex_array->add_vertex_buffer(m_vertex_buffer);
    m_vertex_array->set_index_buffer(m_index_buffer);
    m_vertex_array->unbind();
}

BatchRenderer::~BatchRenderer()
{
    delete m_vertex_array;
    delete m_vertex_buffer;
    delete m_index_buffer;
    delete m_shader;
}

void BatchRenderer::begin_scene()
{
    m_shader->set_mat4("u_mvp", m_renderer->get_camera()->get_view_projection());
    start_batch();
}
void BatchRenderer::end_scene()
{
    flush();
}
void BatchRenderer::start_batch()
{
    m_index_count = 0;
    reset_vertex_buffer_ptr();
}
void BatchRenderer::next_batch()
{
    flush();
    start_batch();
}
void BatchRenderer::flush()
{
    m_shader->bind();
    auto vao_bind = VertexArrayBind(m_vertex_array);

    if(!m_index_count)
        // nothing to draw
        return;
    // how much of vertex buffer base is actually used
    uint32_t data_size {static_cast<uint32_t>(
        reinterpret_cast<const uint8_t*>(get_vertex_buffer_ptr()) -
        reinterpret_cast<const uint8_t*>(get_vertex_buffer_base()))};
    m_vertex_buffer->set_data(get_vertex_buffer_base(), data_size);

    m_renderer->draw(m_index_count);

    m_shader->unbind();
}

} // namespace Maki
