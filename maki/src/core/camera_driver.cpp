#include "pch.h"

#include "camera_driver.h"

namespace Maki {

CameraDriver::CameraDriver(Renderer* renderer)
    : m_renderer {renderer}
{
    set_event_handler();
}

bool CameraDriver::on_key_press(Key key)
{
    switch(key) {
    case Key::w:
        m_vel.z += m_speed;
        return true;
    case Key::s:
        m_vel.z -= m_speed;
        return true;
    case Key::a:
        m_vel.x -= m_speed;
        return true;
    case Key::d:
        m_vel.x += m_speed;
        return true;
    case Key::left_shift:
        m_vel.y += m_speed;
        return true;
    case Key::left_control:
        m_vel.y -= m_speed;
        return true;
    default:
        return false;
    }
}
bool CameraDriver::on_key_release(Key key)
{
    switch(key) {
    case Key::w:
        m_vel.z -= m_speed;
        return true;
    case Key::s:
        m_vel.z += m_speed;
        return true;
    case Key::a:
        m_vel.x += m_speed;
        return true;
    case Key::d:
        m_vel.x -= m_speed;
        return true;
    case Key::left_shift:
        m_vel.y -= m_speed;
        return true;
    case Key::left_control:
        m_vel.y += m_speed;
        return true;
    default:
        return false;
    }
}
bool CameraDriver::on_mouse_btn_press(MouseBtn btn)
{
    switch(btn) {
    case MouseBtn::button_left:
        m_capture_mouse = true;
        // hide cursor
        m_renderer->set_cursor_type(CursorType::disabled);
        return true;
    default:
        return false;
    }
}
bool CameraDriver::on_mouse_btn_release(MouseBtn btn)
{
    switch(btn) {
    case MouseBtn::button_left:
        m_capture_mouse = false;
        m_renderer->set_cursor_type(CursorType::normal);
        return true;
    default:
        return false;
    }
}
bool CameraDriver::on_mouse_move(double pos_x, double pos_y)
{
    m_cur_mouse_pos = {pos_x, pos_y};
    if(m_capture_mouse)
        return true;
    m_last_mouse_pos = m_cur_mouse_pos;
    return false;
}

void CameraDriver::set_event_handler()
{
    EventHandler event_handler;
    event_handler.on_key_press = [this](Key key) {
        return on_key_press(key);
    };
    event_handler.on_key_release = [this](Key key) {
        return on_key_release(key);
    };
    event_handler.on_mouse_btn_press = [this](MouseBtn btn) {
        return on_mouse_btn_press(btn);
    };
    event_handler.on_mouse_btn_release = [this](MouseBtn btn) {
        return on_mouse_btn_release(btn);
    };
    event_handler.on_mouse_move = [this](double pos_x, double pos_y) {
        return on_mouse_move(pos_x, pos_y);
    };
    m_renderer->set_driver_event_handler(event_handler);
}

void CameraDriver::update(long delta_time)
{
    m_renderer->get_camera()->move(m_vel * float(delta_time) * m_speed);
    if(m_capture_mouse) {
        MAKI_LOG_WARN("{} {}", glm::degrees(m_cur_mouse_pos.x - m_last_mouse_pos.x), glm::degrees(m_cur_mouse_pos.y - m_last_mouse_pos.y));
        m_renderer->get_camera()->rotate((m_cur_mouse_pos - m_last_mouse_pos) * (delta_time * m_rotation_speed));
        m_last_mouse_pos = m_cur_mouse_pos;
    }
}

} // namespace Maki
