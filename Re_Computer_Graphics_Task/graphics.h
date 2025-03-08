#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shader.h"

extern GLuint program;
extern GLuint triangleVB;
extern GLuint vertexArrayID;
extern GLuint indexID;

void setVertex() {
	// vertex buffer 설정
	float v[] = { -0.7 , -0.7 , 0 ,
		0.7, -0.7 , 0 ,
		0 , 0.7 , 0 };
	glGenBuffers(1, &triangleVB); // vertex buffer 생성
	glBindBuffer(GL_ARRAY_BUFFER, triangleVB); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 9, v, GL_STATIC_DRAW); // trianbleVB에 데이터 복사

	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	glBindBuffer(GL_ARRAY_BUFFER, triangleVB);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// index buffer 설정
	unsigned int indices[3] = { 0, 1, 2 };
	glGenBuffers(1, &indexID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 3, indices, GL_STATIC_DRAW);
}