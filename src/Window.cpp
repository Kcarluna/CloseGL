#include <stdio.h>
#include <stdlib.h>
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

static State state = {};

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
	// NOTE(__LUNA__): For normal and rgb only
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		switch (state) {
			case ONE: {
				state = TWO;
			} break;
			case TWO: {
				state = THREE;
			} break;
			case THREE: {
				state = FOUR;
			} break;
			case FOUR: {
				state = ONE;
			} break;
		}
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

MousePos mouse = {};

// FIXME(__LUNA__): There seems to be some mouse drifting happening...
void cursor_callback(GLFWwindow *window, double xPos, double yPos)
{
	int w, h;
	glfwGetWindowSize(window , &w, &h);
	static float lastX = w, lastY = h;

	static bool firstMouse = true;
	if (firstMouse) {
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	const float sensitivity = 0.1f;
	mouse.offsetX = (xPos - lastX) * sensitivity;
	mouse.offsetY = (lastY - yPos) * sensitivity;
	lastX = xPos;
	lastY = yPos;
}

State current_state()
{
	return state;
}

float current_mix()
{
	return mix;
}

MousePos current_mouse_pos()
{
	return mouse;
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

	// NOTE(__LUNA__): Disable on-screen cursor
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, cursor_callback);

	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
		fprintf(stderr, "ERROR: Failed to initialize GLAD\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	return window;
}

// NOTE(__LUNA__): For camera movement
bool move_up(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		return true;
	}
	return false;
}

bool move_down(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		return true;
	}
	return false;
}

bool move_left(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		return true;
	}
	return false;
}

bool move_right(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		return true;
	}
	return false;
}
