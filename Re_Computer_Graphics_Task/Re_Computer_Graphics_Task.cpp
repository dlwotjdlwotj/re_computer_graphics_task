#include "graphics.h"

GLuint program = 0;
GLuint triangleVB = 0;
GLuint vertexArrayID = 0;
GLuint indexID = 0;

float transformAngle = 0.0f;
float rotationAngle = 0.0f;

float cameraDistance = 4;
float phi = 0;
float theta = 0;
float fov = 1.04719755;

double lastX = 0;
double lastY = 0;

void render(GLFWwindow* window);

int main(void) {
	if (!glfwInit()) return -1;

	GLFWwindow* window = glfwCreateWindow(800, 600, "Hello", NULL, NULL);
	glfwMakeContextCurrent(window);
	glewInit();
	glfwSwapInterval(1); // 속도 조절

	getMouseInput(window); // 마우스 입력

	program = loadShaders("shader.vert", "shader.frag");

	setJ3AVertex();

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

	setCameraPosition(width, height);

	glBindVertexArray(vertexArrayID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexID);
	glDrawElements(GL_TRIANGLES, nTriangles[0] * 3, GL_UNSIGNED_INT, 0);

	glfwSwapBuffers(window);
}