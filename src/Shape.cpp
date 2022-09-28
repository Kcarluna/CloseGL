#include <stdio.h>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

void create_textured_rectangle_3d(float *vertices, size_t vertices_count, Textured_Rectangle_3d *textured_rectangle_3d)
{
	glGenVertexArrays(1, &textured_rectangle_3d->VAO);
	glGenBuffers(1, &textured_rectangle_3d->VBO);

	glBindVertexArray(textured_rectangle_3d->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, textured_rectangle_3d->VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices_count, vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	const char *vert_shader = "../shaders/texture_3d.vert";
	const char *frag_shader = "../shaders/texture_3d.frag";
	textured_rectangle_3d->program = load_shaders(vert_shader, frag_shader);

	textured_rectangle_3d->texture1 = generate_texture_3d("../textures/wood.jpg");
	textured_rectangle_3d->texture2 = generate_texture_3d("../textures/face.png");

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textured_rectangle_3d->texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textured_rectangle_3d->texture2);

	textured_rectangle_3d->mix = 0.2f;

	glEnable(GL_DEPTH_TEST);
}

void set_mix_3d(float mix, Textured_Rectangle_3d *textured_rectangle_3d)
{
	textured_rectangle_3d->mix = mix;
}

void render_textured_rectangle_3d(int w, int h, Textured_Rectangle_3d *textured_rectangle_3d)
{
	glUseProgram(textured_rectangle_3d->program);

	// TODO(__LUNA__): Create separate texture function for texture1... remove GL_CLAMP_TO_EDGE
	glUniform1i(glGetUniformLocation(textured_rectangle_3d->program, "texture1"), 0);
	glUniform1i(glGetUniformLocation(textured_rectangle_3d->program, "texture2"), 1);
	glUniform1f(glGetUniformLocation(textured_rectangle_3d->program, "mixture"), textured_rectangle_3d->mix);

	// NOTE(__LUNA__): Transforming from vertex to world coordinates | Rotating around x-axis
	glm::mat4 view = view_matrix(0.0f, 0.0f, -3.0f);
	// NOTE(__LUNA__): Fov of 45, aspect ratio of screen, near plane of frustum, far plane of frustum | Params of proj matrix
	glm::mat4 proj = projection_matrix(45.0f, (float) w / (float) h, 0.1f, 100.0f);

	// NOTE(__LUNA__): Order matters with matrices
	glUniformMatrix4fv(glGetUniformLocation(textured_rectangle_3d->program, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(textured_rectangle_3d->program, "projection"), 1, GL_FALSE, glm::value_ptr(proj));

	glm::vec3 cubePositions[] = {
		glm::vec3( 0.0f,  0.0f,  0.0f), 
		glm::vec3( 2.0f,  5.0f, -15.0f), 
		glm::vec3(-1.5f, -2.2f, -2.5f),  
		glm::vec3(-3.8f, -2.0f, -12.3f),  
		glm::vec3( 2.4f, -0.4f, -3.5f),  
		glm::vec3(-1.7f,  3.0f, -7.5f),  
		glm::vec3( 1.3f, -2.0f, -2.5f),  
		glm::vec3( 1.5f,  2.0f, -2.5f), 
		glm::vec3( 1.5f,  0.2f, -1.5f), 
		glm::vec3(-1.3f,  1.0f, -1.5f)  
	};

	for (size_t i = 0; i < sizeof(cubePositions) / sizeof(cubePositions[0]); i++)
	{
		if (i % 3 == 0) {
			float angle = sin(glfwGetTime()) * 25.0f;
			glm::mat4 model = model_matrix(angle, cubePositions[i].x, cubePositions[i].y, cubePositions[i].z);
			glUniformMatrix4fv(glGetUniformLocation(textured_rectangle_3d->program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		} else {
			glm::mat4 model = model_matrix(20.0f * i, cubePositions[i].x, cubePositions[i].y, cubePositions[i].z);
			glUniformMatrix4fv(glGetUniformLocation(textured_rectangle_3d->program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		}
		glBindVertexArray(textured_rectangle_3d->VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

void delete_textured_rectangle_3d(Textured_Rectangle_3d *textured_rectangle_3d)
{
	glDeleteBuffers(1, &textured_rectangle_3d->VBO);
	glDeleteVertexArrays(1, &textured_rectangle_3d->VAO);
	glDeleteProgram(textured_rectangle_3d->program);
}

void create_textured_rectangle_3d_camera(float *vertices, size_t vertices_count, Textured_Rectangle_3d_camera *textured_rectangle_3d_camera)
{
	glGenVertexArrays(1, &textured_rectangle_3d_camera->VAO);
	glGenBuffers(1, &textured_rectangle_3d_camera->VBO);

	glBindVertexArray(textured_rectangle_3d_camera->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, textured_rectangle_3d_camera->VAO);
	glBufferData(GL_ARRAY_BUFFER, vertices_count, vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	const char *vert_shader = "./shaders/texture_3d.vert";
	const char *frag_shader = "./shaders/texture_3d.frag";
	textured_rectangle_3d_camera->program = load_shaders(vert_shader, frag_shader);

	textured_rectangle_3d_camera->texture1 = generate_texture_3d("../textures/wood.jpg");
	textured_rectangle_3d_camera->texture2 = generate_texture_3d("../textures/face.png");

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textured_rectangle_3d_camera->texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textured_rectangle_3d_camera->texture2);

	textured_rectangle_3d_camera->mix = 0.2f;

	glEnable(GL_DEPTH_TEST);

	// NOTE(__LUNA__): Set default camera positions
	textured_rectangle_3d_camera->cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	textured_rectangle_3d_camera->cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	textured_rectangle_3d_camera->cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
}

void set_mix_3d_camera(float mix, Textured_Rectangle_3d_camera *textured_rectangle_3d_camera)
{
	textured_rectangle_3d_camera->mix = mix;
}

void update_camera(float x, float y, Textured_Rectangle_3d_camera *textured_rectangle_3d_camera)
{
	static float yaw = -90.0f;
	static float pitch = 0.0f;

	yaw += x;
	pitch += y;
	if (pitch >= 89.0f) {
		pitch = 89.0f;
	}
	if (pitch <= -89.0f) {
		pitch = -89.0f;
	}

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	textured_rectangle_3d_camera->cameraFront = glm::normalize(direction);
}

void move_camera(int dir, float dt, Textured_Rectangle_3d_camera *textured_rectangle_3d_camera)
{
	const float camera_speed = 2.5f * dt;
	switch (dir) {
		case 1: {
			// NOTE(__LUNA__): Move UP
			textured_rectangle_3d_camera->cameraPos += camera_speed * textured_rectangle_3d_camera->cameraFront;
		} break;
		case 2: {
			// NOTE(__LUNA__): Move DOWN
			textured_rectangle_3d_camera->cameraPos -= camera_speed * textured_rectangle_3d_camera->cameraFront;
		} break;
		case 3: {
			// NOTE(__LUNA__): Move LEFT
			textured_rectangle_3d_camera->cameraPos -= glm::normalize(glm::cross(textured_rectangle_3d_camera->cameraFront, textured_rectangle_3d_camera->cameraUp)) * camera_speed;
		} break;
		case 4: {
			// NOTE(__LUNA__): Move RIGHT
			textured_rectangle_3d_camera->cameraPos += glm::normalize(glm::cross(textured_rectangle_3d_camera->cameraFront, textured_rectangle_3d_camera->cameraUp)) * camera_speed;
		} break;
	}
}

void render_textured_rectangle_3d_camera(int w, int h, Textured_Rectangle_3d_camera *textured_rectangle_3d_camera)
{
	glUseProgram(textured_rectangle_3d_camera->program);

	glUniform1i(glGetUniformLocation(textured_rectangle_3d_camera->program, "texture1"), 0);
	glUniform1i(glGetUniformLocation(textured_rectangle_3d_camera->program, "texture2"), 0);
	glUniform1i(glGetUniformLocation(textured_rectangle_3d_camera->program, "mixture"), textured_rectangle_3d_camera->mix);

	// NOTE(__LUNA__): Interactable_camera_matrix
	glm::mat4 view = interactable_camera_matrix(textured_rectangle_3d_camera->cameraPos,
												textured_rectangle_3d_camera->cameraFront,
												textured_rectangle_3d_camera->cameraUp);
	glm::mat4 proj = projection_matrix(45.0f, (float) w / (float) h, 0.1f, 100.0f);

	glUniformMatrix4fv(glGetUniformLocation(textured_rectangle_3d_camera->program, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(textured_rectangle_3d_camera->program, "projection"), 1, GL_FALSE, glm::value_ptr(proj));

	glm::vec3 cubePositions[] = {
		glm::vec3( 0.0f,  0.0f,  0.0f), 
		glm::vec3( 2.0f,  5.0f, -15.0f), 
		glm::vec3(-1.5f, -2.2f, -2.5f),  
		glm::vec3(-3.8f, -2.0f, -12.3f),  
		glm::vec3( 2.4f, -0.4f, -3.5f),  
		glm::vec3(-1.7f,  3.0f, -7.5f),  
		glm::vec3( 1.3f, -2.0f, -2.5f),  
		glm::vec3( 1.5f,  2.0f, -2.5f), 
		glm::vec3( 1.5f,  0.2f, -1.5f), 
		glm::vec3(-1.3f,  1.0f, -1.5f)  
	};

	for (size_t i = 0; i < sizeof(cubePositions) / sizeof(cubePositions[0]); i++) {
		if (i % 3 == 0) {
			float angle = sin(glfwGetTime()) * 25.0f;
			glm::mat4 model = model_matrix(angle, cubePositions[i].x, cubePositions[i].y, cubePositions[i].z);
			glUniformMatrix4fv(glGetUniformLocation(textured_rectangle_3d_camera->program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		} else {
			glm::mat4 model = model_matrix(20.0f * i, cubePositions[i].x, cubePositions[i].y, cubePositions[i].z);
			glUniformMatrix4fv(glGetUniformLocation(textured_rectangle_3d_camera->program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		}
		glBindVertexArray(textured_rectangle_3d_camera->VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

void delete_textured_rectangle_3d_camera(Textured_Rectangle_3d_camera *textured_rectangle_3d_camera)
{
	glDeleteBuffers(1, &textured_rectangle_3d_camera->VBO);
	glDeleteVertexArrays(1, &textured_rectangle_3d_camera->VAO);
	glDeleteProgram(textured_rectangle_3d_camera->program);
}
