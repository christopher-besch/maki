#pragma once

#include "atom/atom.h"
#include "atom/renderers/batch_renderer.h"
#include "renderer/renderer.h"

namespace Maki {

// batch renderer
class CuboidRenderer: public BatchRenderer {
public:
    CuboidRenderer(Renderer* renderer);
    ~CuboidRenderer();

    void draw_atom(const CuboidAtom* cuboid);

protected:
    virtual void        reset_vertex_buffer_ptr() override;
    virtual const void* get_vertex_buffer_base() const override { return m_vertex_buffer_base; }
    virtual const void* get_vertex_buffer_ptr() const override { return m_vertex_buffer_ptr; }

    static IndexBuffer* create_index_buffer();

protected:
    struct CuboidVertex {
        vec3 pos;
        vec4 col;
    };

    CuboidVertex* m_vertex_buffer_base {nullptr};
    CuboidVertex* m_vertex_buffer_ptr {nullptr};

protected:
    // how many cuboids in single render call / batch
    static constexpr uint32_t s_max_cuboids {3000};
    // 8 corners
    static constexpr uint32_t s_max_vertices {s_max_cuboids * 8};
    // 6 sides, 2 triangles per side, 3 vertices per triangle = 36
    static constexpr uint32_t s_max_indices {s_max_cuboids * 6 * 2 * 3};
};

} // namespace Maki
