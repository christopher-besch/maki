#include "pch.h"

#include "camera.h"

namespace Maki {

Camera::Camera(uint32_t width, uint32_t height, CameraType type)
    : m_type {type}, m_width {width}, m_height {height}, m_aspect_ratio {float(width) / float(height)}
{
    calc_projection();
}

void Camera::set_fov(float fov)
{
    m_fov = fov;

    outdate_projetion();
}
void Camera::set_type(CameraType type)
{
    m_type = type;

    outdate_projetion();
}
void Camera::set_window_size(uint32_t width, uint32_t height)
{
    m_width        = width;
    m_height       = height;
    m_aspect_ratio = float(width) / float(height);

    outdate_projetion();
}
void Camera::set_position(vec3 position)
{
    m_position = position;

    outdate_view();
}
void Camera::set_rotation(vec2 angle)
{
    m_angle = angle;

    outdate_direction();
}
void Camera::move(vec3 delta)
{
    calc_direction();
    m_position += delta.x * m_right;
    m_position += delta.y * m_up;
    m_position += delta.z * m_direction;

    outdate_view();
}
void Camera::rotate(vec2 delta_angle)
{
    m_angle += delta_angle;
    // can't break your ribs
    m_angle.y = std::clamp(m_angle.y, -PI / 2.0f, PI / 2.0f);

    outdate_direction();
}

const mat4& Camera::get_view_projection() const
{
    calc_view_projection();
    return m_view_projection;
}

// calculate updates //

void Camera::calc_view_projection() const
{
    // cache still valid?
    if(!m_view_projection_outdated)
        return;

    calc_projection();
    calc_view();

    m_view_projection = m_projection * m_view;

    m_view_projection_outdated = false;
}
void Camera::calc_projection() const
{
    if(!m_projection_outdated)
        return;

    switch(m_type) {
    case CameraType::perspective:
        m_projection = glm::perspective(m_fov, m_aspect_ratio, s_near_plane, s_far_plane);
        break;
    case CameraType::orthographic:
        MAKI_RAISE_CRITICAL("Orthographic camera isn't supported yet.");
        break;
    default:
        MAKI_RAISE_CRITICAL("Unsupported camera type.");
        break;
    }
    m_projection_outdated = false;
}
void Camera::calc_view() const
{
    if(!m_view_outdated)
        return;

    calc_direction();

    m_view = glm::lookAt(m_position, m_position + m_direction, m_up);

    m_view_outdated = false;
}
void Camera::calc_direction() const
{
    if(!m_direction_outdated)
        return;

    m_direction = {cos(m_angle.y) * sin(m_angle.x),
                   sin(m_angle.y),
                   cos(m_angle.y) * cos(m_angle.x)};

    m_right = {sin(m_angle.x - PI / 2.0f),
               0.0f,
               cos(m_angle.x - PI / 2.0f)};

    m_up = glm::cross(m_right, m_direction);

    m_direction_outdated = false;
}

void Camera::outdate_view_projection() const
{
    m_view_projection_outdated = true;
}
void Camera::outdate_projetion() const
{
    m_projection_outdated = true;
    outdate_view_projection();
}
void Camera::outdate_view() const
{
    m_view_outdated = true;
    outdate_view_projection();
}
void Camera::outdate_direction() const
{
    m_direction_outdated = true;
    outdate_view();
}

} // namespace Maki
