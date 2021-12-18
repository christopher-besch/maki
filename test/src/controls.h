#pragma once

#include "pch.h"

struct Control {
    vec3  position         = vec3(0, 0, 5);
    float horizontal_angle = PI;
    float vertical_angle   = 0.0f;
    // in units per second
    float speed       = 3.0f;
    float mouse_speed = 0.005f;
};

void compute_mat_from_input(
    Control&    ctrl,
    float       delta_time,
    mat4&       projection,
    mat4&       view,
    GLFWwindow* window);
