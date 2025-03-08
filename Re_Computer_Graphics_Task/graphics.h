#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shader.h"

extern GLuint program;
extern GLuint triangleVB;
extern GLuint vertexArrayID;

void setVertex() {
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
}