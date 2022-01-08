#pragma once

#include "core/definitions.h"
#include "platform/event.h"
#include "renderer/renderer.h"

namespace Maki {

class CameraDriver {
public:
    CameraDriver(Renderer* renderer);

    void  update(long delta_time);
    void  set_speed(float speed) { m_speed = speed; }
    float get_speed() { return m_speed; }

private:
    void set_event_handler();
    // return true when handled
    bool on_key_press(Key key);
    bool on_key_release(Key key);
    bool on_mouse_btn_press(MouseBtn btn);
    bool on_mouse_btn_release(MouseBtn btn);
    bool on_mouse_move(double pos_x, double pos_y);

private:
    // borrowed from RenderDriver -> don't delete in destructor
    Renderer* m_renderer;

    vec3 m_vel {0.0f};
    bool m_capture_mouse {false};
    vec2 m_last_mouse_pos;
    vec2 m_cur_mouse_pos;

    // in units per millisecond
    float m_speed {0.05f};
    // in radians per millisecond
    float m_rotation_speed {0.00003f};
};

} // namespace Maki
