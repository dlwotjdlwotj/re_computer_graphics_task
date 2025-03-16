#version 150 core

const float TEX_DELTA = 0.0001;

in vec3 normal;

uniform vec3 color = vec3(1, 0.5, 0);
uniform vec3 lightColor = vec3(1, 1, 1);
uniform vec3 lightPos = vec3(10, 20, 10);
uniform vec3 cameraPos;

uniform sampler2D diffTex;
uniform sampler2D bumpTex;

uniform float shininess;

in vec3 worldCoord;
in vec2 texCoord;

out vec4 out_Color;

vec3 getColor(vec3 N, vec3 L, vec3 R, vec3 V){
	vec3 ret = texture(diffTex, texCoord).rgb * lightColor * max(0, dot(N, L));
	ret += pow(clamp(dot(R, V), 0, 1), shininess) * lightColor;
	return ret;
}

vec3 getReflection(vec3 N, vec3 L){
	return N*(dot(L,N))*2 - L;
}

mat3 getTBN(vec3 N) {
    vec3 Q1 = dFdx(worldCoord), Q2 = dFdy(worldCoord);
    vec2 st1 = dFdx(texCoord), st2 = dFdy(texCoord);
    float D = st1.s * st2.t - st2.s * st1.t;
	return mat3(normalize((Q1 * st2.t - Q2 * st1.t) * D), normalize((-Q1 * st2.s + Q2 * st1.s) * D), N);
}

vec3 getNormal(){
	vec3 N = normalize(normal);

	mat3 TBN = getTBN(N);
	float Bu = texture(bumpTex, texCoord + vec2(TEX_DELTA, 0)).r - texture(bumpTex, texCoord - vec2(TEX_DELTA, 0)).r;
    float Bv = texture(bumpTex, texCoord + vec2(0, TEX_DELTA)).r - texture(bumpTex, texCoord - vec2(0, TEX_DELTA)).r;
	vec3 bumpVec = vec3(-Bu*15., -Bv*15., 1);
	N = normalize(TBN * bumpVec);

	return N;
}

void main(void)
{
	vec3 N = getNormal();
	vec3 L = normalize(lightPos - worldCoord);
	vec3 V = normalize(cameraPos - worldCoord);
	vec3 R = getReflection(N, L);

	vec3 C = getColor(N, L, R, V);
	
 	vec3 gamma = pow(C, vec3(0.4545));
	
	out_Color = vec4(gamma, 1.0);
}
