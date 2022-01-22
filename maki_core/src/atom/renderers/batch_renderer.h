#pragma once

#include "atom/atom.h"
#include "renderer/renderer.h"

namespace Maki {

// implementation inheritance
// abstract
class BatchRenderer {
public:
    BatchRenderer(Renderer* renderer, VertexBuffer* vertex_buffer, IndexBuffer* index_buffer, Shader* m_shader);
    virtual ~BatchRenderer();

    // can be augmented by implementation
    virtual void begin_scene(const Camera* camera);
    void         end_scene();

protected:
    // reset buffer pointer
    void start_batch();
    // flush and start new batch
    void next_batch();
    // render call
    void flush();

    virtual void reset_vertex_buffer_ptr() = 0;
    // needed because size of a vertex varies from implementation to implementation -> vertex buffer data has to be owned by implementation
    virtual const void* get_vertex_buffer_base() const = 0;
    virtual const void* get_vertex_buffer_ptr() const  = 0;

protected:
    Renderer*     m_renderer {nullptr};
    VertexArray*  m_vertex_array {nullptr};
    VertexBuffer* m_vertex_buffer {nullptr};
    IndexBuffer*  m_index_buffer {nullptr};
    Shader*       m_shader {nullptr};

    uint32_t m_index_count {0};
};

} // namespace Maki
