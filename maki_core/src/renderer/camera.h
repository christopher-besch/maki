#pragma once

#include "core/definitions.h"

namespace Maki {

// handle view-projection matrix
class Camera {
public:
    enum class Type {
        perspective = 0,
        orthographic,
    };

    Camera(uint32_t width, uint32_t height, Camera::Type type);

    void set_type(Camera::Type type);
    void set_window_size(uint32_t width, uint32_t height);
    void set_fov(float fov);
    void set_position(vec3 position);
    // horizontal, vertical
    void set_rotation(vec2 angel);
    // in camera coordinates
    void move(vec3 delta);
    // horizontal, vertical
    void rotate(vec2 angel);

    vec3 get_position() const { return m_position; }
    vec2 get_angle() const { return m_angle; }

    const mat4& get_view_projection() const;
    uint32_t    get_width() const { return m_width; }
    uint32_t    get_height() const { return m_height; }

private:
    // only update what's necessary
    void calc_view_projection() const; // depends on projection and view
    void calc_projection() const;
    void calc_view() const; // depends on direction
    void calc_direction() const;

    // outdate specified and all depending on that
    void outdate_view_projection() const;
    void outdate_projetion() const;
    void outdate_view() const;
    void outdate_direction() const;

private:
    Camera::Type m_type;
    uint32_t     m_width, m_height;
    float        m_aspect_ratio;

    vec3 m_position {0.0f, 0.0f, 10.0f};
    // all angles in radians
    // horizontal, vertical
    // default: look into the screen (negative z)
    vec2  m_angle {PI, 0.0f};
    float m_fov {PI / 4};

    // mainly for caching
    // always normalized
    mutable vec3 m_direction;
    mutable vec3 m_right;
    mutable vec3 m_up;

    mutable mat4 m_projection;
    mutable mat4 m_view;
    mutable mat4 m_view_projection;

    // only update what's changed
    mutable bool m_view_projection_outdated {true};
    mutable bool m_projection_outdated {true};
    mutable bool m_view_outdated {true};
    mutable bool m_direction_outdated {true};

private:
    static constexpr float s_near_plane {0.1f};
    static constexpr float s_far_plane {1000.0f};
};

} // namespace Maki
