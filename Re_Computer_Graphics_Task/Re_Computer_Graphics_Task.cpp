#include "graphics.h"

GLuint program = 0;
GLuint triangleVB = 0;
GLuint vertexArrayID = 0;
GLuint indexID = 0;
GLuint normalVB = 0;
GLuint textureID;
GLuint bumpTexID;

float transformAngle = 0.0f;
float rotationAngle = 0.0f;

float cameraDistance = 4;
float phi = 0;
float theta = 0;
float fov = 1.04719755;

float shininessValue;

double lastX = 0;
double lastY = 0;

vec3 lightPos = vec3(10, 20, 10);
vec3 lightColor = vec3(1, 1, 1);
vec3 diffuseColorVec;
vec3 cameraPos;

int w = 0, h = 0, n = 0;

void render(GLFWwindow* window);

int main(void) {
	if (!glfwInit()) return -1;

	GLFWwindow* window = glfwCreateWindow(800, 600, "Hello", NULL, NULL);
	glfwMakeContextCurrent(window);
	glewInit();
	glfwSwapInterval(1); // 속도 조절

	getMouseInput(window); // 마우스 입력

	stbi_set_flip_vertically_on_load(true); // 뒤집힘 해결

	program = loadShaders("shader.vert", "shader.frag");

	int w = 0, h = 0, n = 0;
	void* buf = NULL;
	setJ3AVertex();
	textureLoading(w, h, n, buf);
	bumpMapping(w, h, n, buf);
	setNormalVertex();
	setTexVertex();

	glEnable(GL_DEPTH_TEST); // depth test

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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(program);

	setCameraPosition(width, height);
	sendShadingInfo();

	glBindVertexArray(vertexArrayID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexID);
	glDrawElements(GL_TRIANGLES, nTriangles[0] * 3, GL_UNSIGNED_INT, 0);

	glfwSwapBuffers(window);
}