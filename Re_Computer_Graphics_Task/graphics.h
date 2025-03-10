#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "shader.h"
#include "j3a.hpp"

using namespace glm;

extern GLuint program;
extern GLuint triangleVB;
extern GLuint vertexArrayID;
extern GLuint indexID;

extern float transformAngle;
extern float rotationAngle;

extern float cameraDistance;
extern float phi;
extern float theta;
extern float fov;

extern double lastX;
extern double lastY;

void setVertex() {
	// vertex buffer ����
	float v[] = { 0 , 0.7 , 0 , // ����� �� �ﰢ���� ���� vertex 6��
		-0.35 , 0 , 0 ,
		0.35 , 0 , 0 ,
		-0.7 , -0.7 , 0 ,
		0 , -0.7 , 0 ,
		0.7 , -0.7 , 0 };
	glGenBuffers(1, &triangleVB); // vertex buffer ����
	glBindBuffer(GL_ARRAY_BUFFER, triangleVB); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 18, v, GL_STATIC_DRAW); // trianbleVB�� ������ ����

	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	glBindBuffer(GL_ARRAY_BUFFER, triangleVB);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// index buffer ����
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

void rotateObject() {
	rotationAngle += 0.01f;
	mat4 rotationMat = rotate(rotationAngle, vec3(0.0f, 1.0f, 0.0f));
	GLuint modelMatLocation = glGetUniformLocation(program, "modelMat");
	glUniformMatrix4fv(modelMatLocation, 1, GL_FALSE, &rotationMat[0][0]);
}

void setCameraPosition(int width, int height) {
	vec4 cameraPosHom = vec4(0, 0, cameraDistance, 0); // ī�޶� �Ÿ�
	cameraPosHom = rotate(mat4(1.0f), theta, vec3(0, 1, 0)) * cameraPosHom; // y�� ȸ��
	cameraPosHom = rotate(mat4(1.0f), phi, vec3(1, 0, 0)) * cameraPosHom; // x�� ȸ��
	vec3 cameraPos = vec3(cameraPosHom);

	// view space
	mat4 viewMat = lookAt(cameraPos, vec3(0.0f), vec3(0, 1, 0));
	GLuint viewMatLocation = glGetUniformLocation(program, "viewMat");;
	glUniformMatrix4fv(viewMatLocation, 1, GL_FALSE, &viewMat[0][0]);

	// projection
	float aspect = (float) width / (float) height;
	mat4 projMat = perspective(fov, aspect, 0.01f, 100.0f);
	GLuint projMatLocation = glGetUniformLocation(program, "projMat");
	glUniformMatrix4fv(projMatLocation, 1, GL_FALSE, &projMat[0][0]);
}

void mouseButtonCB(GLFWwindow* window, int button, int action, int mods) { //Ŭ�� Ȯ��
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		glfwGetCursorPos(window, &lastX, &lastY);
	}
}

void cursorPosCB(GLFWwindow* window, double xpos, double ypos) { // Ŀ�� ������ Ȯ��
	int width, height;
	glfwGetWindowSize(window, &width, &height);

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		theta -= (xpos - lastX) / width * 3.141592;
		phi -= (ypos - lastY) / height * 3.141592;
		lastX = xpos;
		lastY = ypos;
	}
}

void getMouseInput(GLFWwindow* window) {
	glfwSetMouseButtonCallback(window, mouseButtonCB);
	glfwSetCursorPosCallback(window, cursorPosCB);
}