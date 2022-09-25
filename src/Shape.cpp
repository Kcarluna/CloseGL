#include <stdio.h>
#include <iostream>
#include "Shader.h"
#include "Texture.h"
#include "Math.hpp"
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

void render_triangle_with_uniform(float val, Triangle *triangle)
{
	glUseProgram(triangle->program);

	glUniform1f(glGetUniformLocation(triangle->program, "translate"), val);

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

void render_rectangle_with_uniform(float val, Rectangle *rectangle)
{
	glUseProgram(rectangle->program);

	glUniform1f(glGetUniformLocation(rectangle->program, "translate"), val);

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

void create_textured_rectangle(float *vertices, size_t vertices_count, GLuint *indices, size_t indices_count, Textured_Rectangle *textured_rectangle)
{
	glGenVertexArrays(1, &textured_rectangle->VAO);
	glGenBuffers(1, &textured_rectangle->VBO);
	glGenBuffers(1, &textured_rectangle->EBO);

	glBindVertexArray(textured_rectangle->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, textured_rectangle->VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices_count, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, textured_rectangle->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_count, indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
	glEnableVertexAttribArray(0);

	// NOTE(__LUNA__): More practice on offset and stride.... last val is offset
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	const char *vert_shader  = "../shaders/texture.vert";
	const char *frag_shader  = "../shaders/texture.frag";
	textured_rectangle->program = load_shaders(vert_shader, frag_shader);

	textured_rectangle->texture1 = generate_texture("../textures/wood.jpg");
	textured_rectangle->texture2 = generate_texture("../textures/face.png");

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textured_rectangle->texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textured_rectangle->texture2);
}

void set_mix(float mix, Textured_Rectangle *textured_rectangle)
{
	textured_rectangle->mix = mix;
}

void render_textured_rectangle(Textured_Rectangle *textured_rectangle)
{
	glUseProgram(textured_rectangle->program);

	// NOTE(__LUNA__): Activate program before setting uniforms
	glUniform1i(glGetUniformLocation(textured_rectangle->program, "texture1"), 0);
	glUniform1i(glGetUniformLocation(textured_rectangle->program, "texture2"), 1);
	glUniform1f(glGetUniformLocation(textured_rectangle->program, "mixture"), textured_rectangle->mix);

	glm::mat4 trans1 = transform(0.5f, -0.5f, 0.0f);
	// FIXME(__LUNA__): glGetUniformLocation on mat4 not working...... ARGHHHHH | Macos doesn't like mat4 uniforms
	glUniformMatrix4fv(glGetUniformLocation(textured_rectangle->program, "transform"), 1, GL_FALSE, glm::value_ptr(trans1));

	glBindVertexArray(textured_rectangle->VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glm::mat4 trans2 = transform(-0.5f, 0.5f, 0.0f);
	glUniformMatrix4fv(glGetUniformLocation(textured_rectangle->program, "transform"), 1, GL_FALSE, glm::value_ptr(trans2));

	glBindVertexArray(textured_rectangle->VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void delete_textured_rectangle(Textured_Rectangle *textured_rectangle)
{
	glDeleteBuffers(1, &textured_rectangle->VBO);
	glDeleteBuffers(1, &textured_rectangle->EBO);
	glDeleteVertexArrays(1, &textured_rectangle->VAO);
	glDeleteProgram(textured_rectangle->program);
}

void create_textured_rectangle_3d(float *vertices, size_t vertices_count, GLuint *indices, size_t indices_count, Textured_Rectangle *textured_rectangle)
{
	glGenVertexArrays(1, &textured_rectangle->VAO);
	glGenBuffers(1, &textured_rectangle->VBO);
	glGenBuffers(1, &textured_rectangle->EBO);

	glBindVertexArray(textured_rectangle->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, textured_rectangle->VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices_count, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, textured_rectangle->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_count, indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	const char *vert_shader = "../shaders/texture_3d.vert";
	const char *frag_shader = "../shaders/texture_3d.frag";
	textured_rectangle->program = load_shaders(vert_shader, frag_shader);

	textured_rectangle->texture1 = generate_texture_3d("../textures/wood.jpg");
	textured_rectangle->texture2 = generate_texture_3d("../textures/face.png");

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textured_rectangle->texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textured_rectangle->texture2);

	textured_rectangle->mix = 0.2f;
}
void render_textured_rectangle_3d(Textured_Rectangle *textured_rectangle)
{
	glUseProgram(textured_rectangle->program);

	// TODO(__LUNA__): Create separate texture function for texture1... remove GL_CLAMP_TO_EDGE
	glUniform1i(glGetUniformLocation(textured_rectangle->program, "texture1"), 0);
	glUniform1i(glGetUniformLocation(textured_rectangle->program, "texture2"), 1);
	glUniform1f(glGetUniformLocation(textured_rectangle->program, "mixture"), textured_rectangle->mix);

	glBindVertexArray(textured_rectangle->VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
