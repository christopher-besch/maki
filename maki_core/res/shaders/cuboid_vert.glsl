#version 450 core

layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec4 a_col;

uniform mat4 u_mvp;

out vec4 col;

void main()
{
    gl_Position = u_mvp * vec4(a_pos, 1.0);
    col = a_col;
}
