#pragma once

#include "renderer/renderer.h"

namespace Maki {

class OpenGLRenderer: public Renderer {
public:
    OpenGLRenderer(const std::string& title, uint32_t width, uint32_t height, EventHandler driver_event_handler = EventHandler {});
    ~OpenGLRenderer();

    virtual void set_clear_col(vec4 color) override;

    virtual void draw(uint32_t index_count) override;
    virtual void start_frame() override;
    // to be defined when necessary
    // virtual void end_frame() override;
};

} // namespace Maki
