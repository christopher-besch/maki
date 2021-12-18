#include "pch.h"

#include "controls.h"

void compute_mat_from_input(Control& ctrl, float delta_time, mat4& projection, mat4& view, GLFWwindow* window)
{
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    // reset
    glfwSetCursorPos(window, WIDTH / 2.0, HEIGHT / 2.0);

    ctrl.horizontal_angle += ctrl.mouse_speed * delta_time * float(WIDTH / 2.0f - xpos);
    ctrl.vertical_angle += ctrl.mouse_speed * delta_time * float(HEIGHT / 2.0f - ypos);

    vec3 direction(
        cos(ctrl.vertical_angle) * sin(ctrl.horizontal_angle),
        sin(ctrl.vertical_angle),
        cos(ctrl.vertical_angle) * cos(ctrl.horizontal_angle));

    vec3 right = vec3(
        sin(ctrl.horizontal_angle - PI / 2.0f),
        0,
        cos(ctrl.horizontal_angle - PI / 2.0f));

    vec3 up = glm::cross(right, direction);

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        ctrl.position += direction * delta_time * ctrl.speed;
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        ctrl.position -= direction * delta_time * ctrl.speed;
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        ctrl.position += right * delta_time * ctrl.speed;
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        ctrl.position -= right * delta_time * ctrl.speed;
    }

    projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);

    view = glm::lookAt(
        ctrl.position,
        ctrl.position + direction,
        up);
}
