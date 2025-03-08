#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"

using namespace glm;

extern GLuint program;
extern GLuint triangleVB;
extern GLuint vertexArrayID;
extern GLuint indexID;

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

void resize() {
	mat3 scaleMat(0.5, 0, 0,
		0, 0.5, 0,
		0, 0, 1);

	GLuint loc = glGetUniformLocation(program, "transform");
	glUniformMatrix3fv(loc, 1, 0, value_ptr(scaleMat));
}