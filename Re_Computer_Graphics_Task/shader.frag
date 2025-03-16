#version 150 core

in vec3 normal;

uniform vec3 color = vec3(1, 0.5, 0);
uniform vec3 lightColor = vec3(1, 1, 1);
uniform vec3 lightPos = vec3(10, 20, 10);

in vec3 worldCoord;

out vec4 out_Color;

void main(void)
{
	vec3 L = normalize(lightPos - worldCoord);
	vec3 N = normalize(normal);
	vec3 diffuse = color * lightColor * max(0, dot(L, N));
 	vec3 gamma = pow(diffuse, vec3(0.4545));
	
	out_Color = vec4(gamma, 1.0);
}
