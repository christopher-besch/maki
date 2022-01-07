#include "pch.h"

#include "cuboid_renderer.h"

namespace Maki {

CuboidRenderer::CuboidRenderer(Renderer* renderer)
    : m_renderer {renderer},
      m_vertex_array {VertexArray::create()},
      m_vertex_buffer {VertexBuffer::create(
          {{"a_pos", DataType::float3},
           {"a_col", DataType::float4}},
          s_max_vertices * sizeof(CuboidVertex))},
      m_vertex_buffer_base {new CuboidVertex[s_max_cuboids]}
{
    m_vertex_array->add_vertex_buffer(m_vertex_buffer);

    uint32_t* indices {new uint32_t[s_max_indices]};

    uint32_t offset {0};
    for(uint32_t i {0}; i < s_max_indices; i += 36) {
        // bottom
        indices[i + 0] = offset + 2;
        indices[i + 1] = offset + 3;
        indices[i + 2] = offset + 0;

        indices[i + 3] = offset + 0;
        indices[i + 4] = offset + 3;
        indices[i + 5] = offset + 1;

        // front
        indices[i + 6] = offset + 0;
        indices[i + 7] = offset + 1;
        indices[i + 8] = offset + 5;

        indices[i + 9]  = offset + 5;
        indices[i + 10] = offset + 4;
        indices[i + 11] = offset + 0;

        // left
        indices[i + 12] = offset + 2;
        indices[i + 13] = offset + 0;
        indices[i + 14] = offset + 4;

        indices[i + 15] = offset + 4;
        indices[i + 16] = offset + 6;
        indices[i + 17] = offset + 2;

        // right
        indices[i + 18] = offset + 1;
        indices[i + 19] = offset + 3;
        indices[i + 20] = offset + 7;

        indices[i + 21] = offset + 7;
        indices[i + 22] = offset + 5;
        indices[i + 23] = offset + 1;

        // back
        indices[i + 24] = offset + 3;
        indices[i + 25] = offset + 2;
        indices[i + 26] = offset + 6;

        indices[i + 27] = offset + 6;
        indices[i + 28] = offset + 7;
        indices[i + 29] = offset + 3;

        // top
        indices[i + 30] = offset + 7;
        indices[i + 31] = offset + 6;
        indices[i + 32] = offset + 4;

        indices[i + 33] = offset + 4;
        indices[i + 34] = offset + 5;
        indices[i + 35] = offset + 7;

        offset += 8;
    }
    m_index_buffer = IndexBuffer::create(s_max_indices, indices);
    delete[] indices;
    m_vertex_array->set_index_buffer(m_index_buffer);

    m_shader = Shader::create("maki_core/res/shaders/cuboid_vert.glsl", "maki_core/res/shaders/cuboid_frag.glsl");
}

CuboidRenderer::~CuboidRenderer()
{
    delete m_vertex_array;
    delete m_vertex_buffer;
    delete m_index_buffer;
    delete m_shader;
    delete[] m_vertex_buffer_base;
}

void CuboidRenderer::begin_scene(const Camera* camera)
{
    MAKI_LOG_EXTRA("start");
    m_shader->set_mat4("u_mvp", camera->get_view_projection());
    start_batch();
}
void CuboidRenderer::end_scene()
{
    flush();
    MAKI_LOG_EXTRA("end");
}
void CuboidRenderer::start_batch()
{
    m_index_count       = 0;
    m_vertex_buffer_ptr = m_vertex_buffer_base;
}
void CuboidRenderer::next_batch()
{
    flush();
    start_batch();
}
void CuboidRenderer::flush()
{
    MAKI_LOG_EXTRA("flush");
    // how much of vertex buffer base is actually used
    uint32_t data_size {static_cast<uint32_t>(
        reinterpret_cast<uint8_t*>(m_vertex_buffer_ptr) -
        reinterpret_cast<uint8_t*>(m_vertex_buffer_base))};
    m_vertex_buffer->set_data(m_vertex_buffer_base, data_size);
    m_renderer->draw(m_vertex_array, m_shader, m_index_count);
}

void CuboidRenderer::draw_cuboid(const CuboidAtom* cuboid)
{
    if(!cuboid->render)
        return;
    for(uint32_t i {0}; i < 8; ++i) {
        m_vertex_buffer_ptr->pos = cuboid->ver_pos[i];
        m_vertex_buffer_ptr->col = cuboid->ver_col[i];
        ++m_vertex_buffer_ptr;
    }
    m_index_count += 36;
}

} // namespace Maki
