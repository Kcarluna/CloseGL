#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <glad/glad.h>
#include "Window.h"

#define WIDTH 1024
#define HEIGHT 768

// FIXME(__LUNA__): Need to implement a system for inputs... input.c
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	(void) window;
	glViewport(0, 0, width, height);
}

static State state = {0};

float mix = 0.2f;

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	(void) scancode;
	(void) mods;
	static bool toggle = false;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		glPolygonMode(GL_FRONT_AND_BACK, (toggle = !toggle) ? GL_LINE : GL_FILL);
	}
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		state++;
		state = (state == END) ? ONE : state;
	}

	if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
		if (mix <= 1.0f) {
			mix += 0.1f;
		}
	}
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
		if (mix >= 0.1f) {
			mix -= 0.1f;
		}
	}
}

State current_state()
{
	return state;
}

float current_mix()
{
	return mix;
}

GLFWwindow *create_window()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif //__APPLE__

	const char *title = "OpenGL practice";
	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, title, NULL, NULL);
	if (!window) {
		fprintf(stderr, "ERROR: Failed to initialize GLFW window\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	// NOTE(__LUNA__): Normalizes viewport..... need to do more research
	//	glViewport(0, 0, WIDTH, HEIGHT);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);

	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
		fprintf(stderr, "ERROR: Failed to initialize GLAD\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	return window;
}
