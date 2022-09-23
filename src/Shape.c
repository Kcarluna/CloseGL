#include <stdio.h>
#include "Shader.h"
#include "Shape.h"

void create_triangle(float *vertices, size_t vertices_count, Triangle *triangle)
{
	glGenVertexArrays(1, &triangle->VAO);
	glGenBuffers(1, &triangle->VBO);

	glBindVertexArray(triangle->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, triangle->VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices_count, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
	glEnableVertexAttribArray(0);

	const char *vert_shader = "../shaders/yellow.vert";
	const char *frag_shader = "../shaders/yellow.frag";
	triangle->program = load_shaders(vert_shader, frag_shader);
}

void create_rgb_triangle(float *vertices, size_t vertices_count, Triangle *triangle)
{
	// NOTE(__LUNA__): Bug in OSX where vertex output and fragment input need to have the same name...
	// otherwise nasty bug with absolutely no way of debugging.

	glGenVertexArrays(1, &triangle->VAO);
	glGenBuffers(1, &triangle->VBO);

	glBindVertexArray(triangle->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, triangle->VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices_count, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	const char *vert_shader  = "../shaders/rgb.vert";
	const char *frag_shader  = "../shaders/rgb.frag";
	triangle->program = load_shaders(vert_shader, frag_shader);
}

void render_triangle(Triangle *triangle)
{
	glUseProgram(triangle->program);
	glBindVertexArray(triangle->VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void delete_triangle(Triangle *triangle)
{
	glDeleteBuffers(1, &triangle->VBO);
	glDeleteVertexArrays(1, &triangle->VAO);
	glDeleteProgram(triangle->program);
}

void create_rectangle(float *vertices, size_t vertices_count, GLuint *indices, size_t indices_count, Rectangle *rectangle)
{
	glGenVertexArrays(1, &rectangle->VAO);
	glGenBuffers(1, &rectangle->VBO);
	glGenBuffers(1, &rectangle->EBO);

	glBindVertexArray(rectangle->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, rectangle->VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices_count, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rectangle->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_count, indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
	glEnableVertexAttribArray(0);

	// NOTE(__LUNA__): NO need to unbind buffers.... rarely causes any issues
//	// NOTE(__LUNA__): Unbind buffer
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
//	// NOTE(__LUNA__): DO NOT unbind EBO buffer before unbinding VAO
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	const char *vert_shader  = "../shaders/yellow.vert";
	const char *frag_shader  = "../shaders/yellow.frag";
	rectangle->program = load_shaders(vert_shader, frag_shader);
}

void create_rgb_rectangle(float *vertices, size_t vertices_count, GLuint *indices, size_t indices_count, Rectangle *rectangle)
{

	glGenVertexArrays(1, &rectangle->VAO);
	glGenBuffers(1, &rectangle->VBO);
	glGenBuffers(1, &rectangle->EBO);

	glBindVertexArray(rectangle->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, rectangle->VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices_count, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rectangle->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_count, indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	const char *vert_shader  = "../shaders/rgb.vert";
	const char *frag_shader  = "../shaders/rgb.frag";
	rectangle->program = load_shaders(vert_shader, frag_shader);
}

void render_rectangle(Rectangle *rectangle)
{
	glUseProgram(rectangle->program);
	glBindVertexArray(rectangle->VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void delete_rectangle(Rectangle *rectangle)
{
	glDeleteBuffers(1, &rectangle->VBO);
	glDeleteBuffers(1, &rectangle->EBO);
	glDeleteVertexArrays(1, &rectangle->VAO);
	glDeleteProgram(rectangle->program);
}
