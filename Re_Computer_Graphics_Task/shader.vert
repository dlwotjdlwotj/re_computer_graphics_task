#version 410 core

layout(location=0) in vec3 in_Position;
uniform mat3 transform;
vec2 p2;

// transform matrix에 기존 벡터 p2를 곱해 크기를 바꿈
void Scale(){
	vec3 p = transform*vec3(p2, 1.0);
	p2=p.xy;
}

void main(void)
{
	p2 = in_Position.xy;
	Scale();
	gl_Position= vec4(p2, 0, 1);
}
