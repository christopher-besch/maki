#pragma once

#include "atom/atom.h"
#include "renderer/renderer.h"

namespace Maki {

class CuboidRenderer {
public:
    CuboidRenderer(Renderer* renderer);
    ~CuboidRenderer();

    void begin_scene(const Camera* camera);
    void end_scene();
    // reset buffer pointer
    void start_batch();
    // flush and start new batch
    void next_batch();
    // render call
    void flush();

    void draw_cuboid(const CuboidAtom* cuboid);

private:
    struct CuboidVertex {
        vec3 pos;
        vec4 col;
    };

    Renderer*     m_renderer;
    VertexArray*  m_vertex_array {nullptr};
    VertexBuffer* m_vertex_buffer {nullptr};
    IndexBuffer*  m_index_buffer {nullptr};
    Shader*       m_shader {nullptr};

    uint32_t      m_index_count {0};
    CuboidVertex* m_vertex_buffer_base {nullptr};
    CuboidVertex* m_vertex_buffer_ptr {nullptr};

private:
    // how many cuboids in single render call
    static constexpr uint32_t s_max_cuboids {2000};
    // 8 corners
    static constexpr uint32_t s_max_vertices {s_max_cuboids * 8};
    // 6 sides, 2 triangles per side, 3 vertices per triangle = 36
    static constexpr uint32_t s_max_indices {s_max_cuboids * 6 * 2 * 3};
};

} // namespace Maki
