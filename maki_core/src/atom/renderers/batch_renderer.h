#pragma once

#include "atom/atom.h"
#include "renderer/renderer.h"

namespace Maki {

// implementation inheritance
// abstract
class BatchRenderer {
public:
    BatchRenderer(Renderer* renderer, VertexBuffer* vertex_buffer, IndexBuffer* index_buffer, Shader* shader);
    virtual ~BatchRenderer();

    // can be augmented by implementation
    virtual void begin_scene();
    void         end_scene();

    // to be defined by implementation
    // void draw_atom(const AtomType& atom);

protected:
    // reset buffer pointer
    void start_batch();
    // flush and start new batch
    void next_batch();
    // render call
    void flush();

    virtual void reset_vertex_buffer_ptr() = 0;
    // void needed because size of a vertex varies from implementation to implementation -> vertex buffer data has to be owned by implementation
    virtual const void* get_vertex_buffer_base() const = 0;
    virtual const void* get_vertex_buffer_ptr() const  = 0;

protected:
    uint32_t m_index_count {0};

private:
    Renderer*     m_renderer {nullptr};
    VertexArray*  m_vertex_array {nullptr};
    VertexBuffer* m_vertex_buffer {nullptr};
    IndexBuffer*  m_index_buffer {nullptr};
    Shader*       m_shader {nullptr};
};

} // namespace Maki
