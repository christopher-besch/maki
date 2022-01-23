#include "pch.h"

#include "quadrilateral_renderer.h"

namespace Maki {

QuadrilateralRenderer::QuadrilateralRenderer(Renderer* renderer)
    : BatchRenderer {
          renderer,
          VertexBuffer::create(
              {{"a_pos", DataType::float3},
               {"a_col", DataType::float4}},
              s_max_vertices * sizeof(Vertex)),
          create_index_buffer(),
          // TODO: use shader that renders both sides
          Shader::create("maki_core/res/shaders/cuboid_vert.glsl", "maki_core/res/shaders/cuboid_frag.glsl")},
      m_vertex_buffer_base {new Vertex[s_max_vertices]}
{
}

QuadrilateralRenderer::~QuadrilateralRenderer()
{
    delete[] m_vertex_buffer_base;
}

void QuadrilateralRenderer::draw_atom(const QuadrilateralAtom* atom)
{
    if(!atom->render)
        return;
    if(m_index_count >= s_max_indices)
        next_batch();
    for(uint32_t i {0}; i < 4; ++i) {
        m_vertex_buffer_ptr->pos = atom->ver_pos[i];
        m_vertex_buffer_ptr->col = atom->ver_col[i];
        ++m_vertex_buffer_ptr;
    }
    m_index_count += 6;
}

// TODO: remove code duplication
void QuadrilateralRenderer::reset_vertex_buffer_ptr()
{
    m_vertex_buffer_ptr = m_vertex_buffer_base;
}

IndexBuffer* QuadrilateralRenderer::create_index_buffer()
{
    uint32_t* indices {new uint32_t[s_max_indices]};

    uint32_t offset {0};
    for(uint32_t i {0}; i < s_max_indices; i += 6) {
        indices[i + 0] = offset + 2;
        indices[i + 1] = offset + 0;
        indices[i + 2] = offset + 3;

        indices[i + 3] = offset + 3;
        indices[i + 4] = offset + 0;
        indices[i + 5] = offset + 1;

        offset += 4;
    }
    IndexBuffer* index_buffer = IndexBuffer::create(s_max_indices, indices);
    delete[] indices;
    return index_buffer;
}

} // namespace Maki
