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

out vec4 color;

void main()
{
	color = vec4(1,0,0,1);
}
