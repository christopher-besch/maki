#pragma once

#include "core/definitions.h"

namespace Maki {

enum class CameraType {
    perspective = 0,
    orthographic,
};

class Camera {
public:
    Camera(uint32_t width, uint32_t height, CameraType = CameraType::perspective);

    void set_type(CameraType type);
    void set_window_size(uint32_t width, uint32_t height);
    void set_fov(float fov);
    void set_position(vec3 position);
    // horizontal, vertical
    void set_rotation(vec2 angel);
    // in camera coordinates
    void move(vec3 delta);
    // horizontal, vertical
    void rotate(vec2 angel);

    vec3 get_position() { return m_position; }
    vec2 get_angle() { return m_angle; }

    const mat4& get_view_projection();
    uint32_t    get_width() { return m_width; }
    uint32_t    get_height() { return m_height; }

private:
    // only update what's necessary
    void calc_view_projection(); // depends on projection and view
    void calc_projection();
    void calc_view(); // depends on direction
    void calc_direction();

    // outdate specified and all depending on that
    void outdate_view_projection();
    void outdate_projetion();
    void outdate_view();
    void outdate_direction();

private:
    CameraType m_type;
    uint32_t   m_width, m_height;
    float      m_aspect_ratio;

    vec3 m_position {0.0f, 0.0f, 10.0f};
    // all angles in radians
    // horizontal, vertical
    // default: look into the screen (negative z)
    vec2  m_angle {PI, 0.0f};
    float m_fov {PI / 4};

    // mainly for caching
    // always normalized
    vec3 m_direction;
    vec3 m_right;
    vec3 m_up;

    mat4 m_projection;
    mat4 m_view;
    mat4 m_view_projection;

    // only update what's changed
    bool m_view_projection_outdated {true};
    bool m_projection_outdated {true};
    bool m_view_outdated {true};
    bool m_direction_outdated {true};
};

} // namespace Maki
