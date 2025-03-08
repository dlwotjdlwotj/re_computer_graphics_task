﻿#include "graphics.h"

GLuint program = 0;
GLuint triangleVB = 0;
GLuint vertexArrayID = 0;
GLuint indexID = 0;

float transformAngle = 0.0f;

void render(GLFWwindow* window);

int main(void) {
	if (!glfwInit()) return -1;

	GLFWwindow* window = glfwCreateWindow(800, 600, "Hello", NULL, NULL);
	glfwMakeContextCurrent(window);
	glewInit();
	glfwSwapInterval(1); // buffer swap 주기 설정(회전 속도 조절 목적)

	program = loadShaders("shader.vert", "shader.frag");

	setVertex();

	while (!glfwWindowShouldClose(window)) {
		render(window);
		glfwPollEvents();
	}
		
	glfwDestroyWindow(window);
	glfwTerminate();
}
void render(GLFWwindow* window) {
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	glClearColor(0, 0, .5, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(program);

	transform();

	glBindVertexArray(vertexArrayID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexID);
	glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

	glfwSwapBuffers(window);
}