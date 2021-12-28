#pragma once

#include "renderer/renderer.h"

namespace Maki {

class OpenGLRenderer: public Renderer {
public:
    OpenGLRenderer(const std::string& title, uint32_t width, uint32_t height, EventHandler driver_event_handler = EventHandler {});
    ~OpenGLRenderer();

    virtual void set_clear_col(vec4 color) override;

    virtual void draw(VertexArray* vertex_array, IndexBuffer* index_buffer, Shader* shader) override;
    virtual void start_frame() override;
    // to be defined when necessary
    // virtual void end_frame() override;

protected:
    virtual void set_viewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
};

} // namespace Maki
