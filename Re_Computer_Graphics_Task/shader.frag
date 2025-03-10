#version 150 core

in vec3 normal;

out vec4 out_Color;

void main(void)
{
	out_Color = vec4(normal, 1.0);
}
