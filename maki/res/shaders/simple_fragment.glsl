#version 450 core

/* // interpolated from vertex shader */
/* in vec2 uv;  */

/* out vec3 color; */

/* // constant for whole mesh */
/* uniform sampler2D texture_sampler; */

/* void main() */
/* { */
/*     color = texture(texture_sampler, uv).rgb; */
/* } */

in vec3 pos;

uniform vec3 u_color;

out vec3 color;

void main()
{
	color = u_color;
}
