#pragma once

#include "atom/atoms/quadrilateral_atom.h"
#include "atom/renderers/batch_renderer.h"
#include "renderer/renderer.h"

namespace Maki {

// batch renderer
class QuadrilateralRenderer: public BatchRenderer {
public:
    QuadrilateralRenderer(Renderer* renderer);
    ~QuadrilateralRenderer();

    void draw_atom(const QuadrilateralAtom* atom);

protected:
    virtual void        reset_vertex_buffer_ptr() override;
    virtual const void* get_vertex_buffer_base() const override { return m_vertex_buffer_base; }
    virtual const void* get_vertex_buffer_ptr() const override { return m_vertex_buffer_ptr; }

    static IndexBuffer* create_index_buffer();

protected:
    struct Vertex {
        vec3 pos;
        vec4 col;
    };

    Vertex* m_vertex_buffer_base {nullptr};
    Vertex* m_vertex_buffer_ptr {nullptr};

protected:
    // how many cuboids in single render call / batch
    static constexpr uint32_t s_max_quadrilaterals {12000};
    // 4 corners
    static constexpr uint32_t s_max_vertices {s_max_quadrilaterals * 4};
    // 1 side, 2 triangles per side, 3 vertices per triangle = 36
    static constexpr uint32_t s_max_indices {s_max_quadrilaterals * 1 * 2 * 3};
};

} // namespace Maki
