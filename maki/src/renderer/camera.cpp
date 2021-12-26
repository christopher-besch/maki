#include "pch.h"

#include "camera.h"
#include "core/log.h"

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
void Camera::set_rotation(float hor_angle, float ver_angle)
{
    m_hor_angle = hor_angle;
    m_ver_angle = ver_angle;

    outdate_direction();
}
void Camera::move(vec3 delta)
{
    m_position += delta;

    outdate_view();
}
void Camera::rotate(float delta_hor, float delta_ver)
{
    m_hor_angle += delta_hor;
    m_ver_angle += delta_ver;

    outdate_direction();
}

const mat4& Camera::get_view_projection()
{
    calc_view_projection();
    return m_view_projection;
}

// calculate updates //

void Camera::calc_view_projection()
{
    // cache still valid?
    if(!m_view_projection_outdated)
        return;
    MAKI_LOG_GENERAl("Calculate camera view projection.");

    calc_projection();
    calc_view();

    m_view_projection = m_projection * m_view;

    m_view_projection_outdated = false;
}
void Camera::calc_projection()
{
    if(!m_projection_outdated)
        return;
    MAKI_LOG_GENERAl("Calculate camera projection.");

    switch(m_type) {
    case CameraType::perspective:
        m_projection = glm::perspective(m_fov, m_aspect_ratio, 0.1f, 100.0f);
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
void Camera::calc_view()
{
    if(!m_view_outdated)
        return;
    MAKI_LOG_GENERAl("Calculate camera view.");

    calc_direction();

    m_view = glm::lookAt(m_position, m_position + m_direction, m_up);

    m_view_outdated = false;
}
void Camera::calc_direction()
{
    if(!m_direction_outdated)
        return;
    MAKI_LOG_GENERAl("Calculate camera direction.");

    m_direction = {cos(m_ver_angle) * sin(m_hor_angle),
                   sin(m_ver_angle),
                   cos(m_ver_angle) * cos(m_hor_angle)};

    m_right = {sin(m_hor_angle - PI / 2.0f),
               0.0f,
               cos(m_hor_angle - PI / 2.0f)};

    m_up = glm::cross(m_right, m_direction);

    m_direction_outdated = false;
}

void Camera::outdate_view_projection()
{
    m_view_projection_outdated = true;
}
void Camera::outdate_projetion()
{
    m_projection_outdated = true;
    outdate_view_projection();
}
void Camera::outdate_view()
{
    m_view_outdated = true;
    outdate_view_projection();
}
void Camera::outdate_direction()
{
    m_direction_outdated = true;
    outdate_view();
}

} // namespace Maki
