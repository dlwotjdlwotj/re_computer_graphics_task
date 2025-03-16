#version 150 core

in vec3 normal;

uniform vec3 color = vec3(1, 0.5, 0);
uniform vec3 lightColor = vec3(1, 1, 1);
uniform vec3 lightPos = vec3(10, 20, 10);
uniform vec3 cameraPos;

uniform float shininess;

in vec3 worldCoord;

out vec4 out_Color;

vec3 getColor(vec3 N, vec3 L){
	return color * lightColor * max(0, dot(N, L));
}

vec3 getReflection(vec3 N, vec3 L){
	return N*(dot(L,N))*2 - L;
}

void main(void)
{
	vec3 L = normalize(lightPos - worldCoord);
	vec3 N = normalize(normal);
	vec3 V = normalize(cameraPos - worldCoord);
	vec3 R = getReflection(N, L);

	vec3 C = getColor(N, L);
	C += pow(clamp(dot(R, V), 0, 1), shininess) * lightColor;
 	vec3 gamma = pow(C, vec3(0.4545));
	
	out_Color = vec4(gamma, 1.0);
}
