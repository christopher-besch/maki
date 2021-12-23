#version 330 core

// interpolated from vertex shader
in vec2 uv; 

out vec3 color;

// constant for whole mesh
uniform sampler2D texture_sampler;

void main()
{
    color = texture(texture_sampler, uv).rgb;
    a;lsdlkfjsd;dlfkasja;lskdjf;alsd
}
