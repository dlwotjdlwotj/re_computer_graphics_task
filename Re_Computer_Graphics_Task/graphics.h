#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "j3a.hpp"

using namespace glm;

extern GLuint program;
extern GLuint triangleVB;
extern GLuint vertexArrayID;
extern GLuint indexID;

extern float transformAngle;

void setVertex() {
	// vertex buffer 설정
	float v[] = { 0 , 0.7 , 0 , // 가운데가 빈 삼각형을 위한 vertex 6개
		-0.35 , 0 , 0 ,
		0.35 , 0 , 0 ,
		-0.7 , -0.7 , 0 ,
		0 , -0.7 , 0 ,
		0.7 , -0.7 , 0 };
	glGenBuffers(1, &triangleVB); // vertex buffer 생성
	glBindBuffer(GL_ARRAY_BUFFER, triangleVB); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 18, v, GL_STATIC_DRAW); // trianbleVB에 데이터 복사

	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	glBindBuffer(GL_ARRAY_BUFFER, triangleVB);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// index buffer 설정
	unsigned int indices[9] = { 0, 1, 2 , 1, 3, 4 , 2, 4, 5 };
	glGenBuffers(1, &indexID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 9, indices, GL_STATIC_DRAW);
}

void setJ3AVertex() {
	loadJ3A("C:/program1/Re_Computer_Graphics_Task/Re_Computer_Graphics_Task/banana.j3a");

	glGenBuffers(1, &triangleVB);
	glBindBuffer(GL_ARRAY_BUFFER, triangleVB);
	glBufferData(GL_ARRAY_BUFFER, nVertices[0] * sizeof(vec3), vertices[0], GL_STATIC_DRAW);

	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	glBindBuffer(GL_ARRAY_BUFFER, triangleVB);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glGenBuffers(1, &indexID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, nTriangles[0] * sizeof(u32vec3), triangles[0], GL_STATIC_DRAW);
}

void resize() {
	mat3 scaleMat(0.5, 0, 0,
		0, 0.5, 0,
		0, 0, 1);

	GLuint loc = glGetUniformLocation(program, "transform");
	glUniformMatrix3fv(loc, 1, 0, value_ptr(scaleMat));
}

void rotate() {
	transformAngle += 0.05f;
	mat3 rotMat(cos(transformAngle), sin(transformAngle), 0,
		-sin(transformAngle), cos(transformAngle), 0,
		0, 0, 1);

	GLuint loc = glGetUniformLocation(program, "transform");
	glUniformMatrix3fv(loc, 1, 0, glm::value_ptr(rotMat));
}

void transform() {
	mat3 scaleMat(0.5, 0, 0,
		0, 0.5, 0,
		0, 0, 1);

	transformAngle += 0.05f;
	mat3 rotMat(cos(transformAngle), sin(transformAngle), 0,
		-sin(transformAngle), cos(transformAngle), 0,
		0, 0, 1);

	mat3 finalMat = scaleMat * rotMat;
	
	GLuint loc = glGetUniformLocation(program, "transform");
	glUniformMatrix3fv(loc, 1, 0, glm::value_ptr(finalMat));
}