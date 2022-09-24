#ifdef __APPLE__
	#define GL_SILENCE_DEPRECATION
#endif //__APPLE__
#include <stdio.h>
#include <GLFW/glfw3.h>
#include "Window.h"
#include "Shape.h"
#include "Sandbox.h"

void run_normal()
{
	GLFWwindow *window = create_window();

	Triangle triangle_one = {0};
	Triangle triangle_two = {0};
	Rectangle rectangle = {0};

	float triangle_one_vertices[] = {
		// positions
		-0.5f, -0.5f, 0.0f, // bottom left
		0.5f, -0.5f, 0.0f,  // bottom right
		0.0f,  0.5f, 0.0f   // top
	};

	float triangle_two_vertices[] = {
		// positions
		-0.5f, -0.5f, 0.0f, // bottom left
		0.5f, -0.5f, 0.0f,  // bottom right
		0.0f,  0.5f, 0.0f   // top
	};

	float rectangle_vertices[] = {
		// positions
		  0.5f, 0.5f, 0.0f, // top right
		 0.5f, -0.5f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f, // bottom left
		- 0.5f, 0.5f, 0.0f, // top left
	};
	GLuint rectangle_indices[] = {
		0, 1, 3,
		1, 2, 3,
	};

	create_triangle(triangle_one_vertices, sizeof(triangle_one_vertices), &triangle_one);
	create_triangle(triangle_one_vertices, sizeof(triangle_two_vertices), &triangle_two);
	create_rectangle(rectangle_vertices, sizeof(rectangle_vertices), rectangle_indices, sizeof(rectangle_indices), &rectangle);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// NOTE(__LUNA__): Not happy with this... 'state' machine
		switch (current_state()) {
			case ONE: {
				render_triangle_with_uniform(0.0f, &triangle_one);
			} break;
			case TWO: {
				render_triangle_with_uniform(0.0f, &triangle_two);
			} break;
			case THREE: {
				render_rectangle_with_uniform(0.0f, &rectangle);
			} break;
			case FOUR: {
				render_triangle_with_uniform(-0.5f, &triangle_one);
				render_triangle_with_uniform(0.5f, &triangle_two);
				render_rectangle_with_uniform(0.0f, &rectangle);
			} break;
			default: {
			}
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	delete_rectangle(&rectangle);
	delete_triangle(&triangle_two);
	delete_triangle(&triangle_one);

	glfwTerminate();
}

void run_rgb()
{
	GLFWwindow *window = create_window();

	Triangle left_triangle = {0};
	Triangle right_triangle = {0};
	Rectangle rectangle = {0};

	float left_triangle_vertices[] = {
		// positions        // colors
		-1.0f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // bottom left
		 0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom right
		-0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f   // top
	};

	float right_triangle_vertices[] = {
		// positions       // colors
		0.0f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // bottom left
		1.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom right
		0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f   // top
	};

	float rectangle_vertices[] = {
		// positions        // colors
		  0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // top right
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom left
		- 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // top left
	};
	GLuint rectangle_indices[] = {
		0, 1, 3,
		1, 2, 3,
	};

	create_rgb_triangle(left_triangle_vertices, sizeof(left_triangle_vertices), &left_triangle);
	create_rgb_triangle(right_triangle_vertices, sizeof(right_triangle_vertices), &right_triangle);
	create_rgb_rectangle(rectangle_vertices, sizeof(rectangle_vertices), rectangle_indices, sizeof(rectangle_indices), &rectangle);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// NOTE(__LUNA__): Not happy with this... 'state' machine
		switch (current_state()) {
			case ONE: {
				render_triangle(&right_triangle);
			} break;
			case TWO: {
				render_triangle(&left_triangle);
			} break;
			case THREE: {
				render_rectangle(&rectangle);
			} break;
			case FOUR: {
				render_triangle(&right_triangle);
				render_triangle(&left_triangle);
				render_rectangle(&rectangle);
			} break;
			default: {
			}
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	delete_rectangle(&rectangle);
	delete_triangle(&right_triangle);
	delete_triangle(&left_triangle);

	glfwTerminate();
}

void run_texture()
{
	GLFWwindow *window = create_window();

	Textured_Rectangle textured_rectangle = {0};

	float vertices[] = {
		 // positions         // colors           // texture coords (s, t) | Increasing s\t 'duplicates' textures
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   2.0f, 2.0f,   // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   2.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 2.0f    // top left
	};
	GLuint indices[] = {
		0, 1, 3,
		1, 2, 3,
	};

	create_textured_rectangle(vertices, sizeof(vertices), indices, sizeof(indices), &textured_rectangle);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// NOTE(__LUNA__): Errrr
		set_mix(current_mix(), &textured_rectangle);

		render_textured_rectangle(&textured_rectangle);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	delete_textured_rectangle(&textured_rectangle);

	glfwTerminate();
}
