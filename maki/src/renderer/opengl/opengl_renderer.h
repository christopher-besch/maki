#pragma once

#include "renderer/renderer.h"

namespace Maki {

class OpenGLRenderer: public Renderer {
public:
    OpenGLRenderer(const std::string& title, uint32_t width, uint32_t height);
    ~OpenGLRenderer();

    virtual void draw(VertexArray* vertex_array, IndexBuffer* index_buffer, Shader* shader) override;

    virtual void end_frame() override;
};

} // namespace Maki
