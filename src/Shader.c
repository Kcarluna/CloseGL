#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Shader.h"

void load_shader_src(const char *src, GLuint shader)
{
	glShaderSource(shader, 1, &src, NULL);
}

bool load_shader_file(const char *file_path, GLuint shader)
{
	FILE *file = fopen(file_path, "r");
	if (!file) {
		fprintf(stderr, "ERROR: Failed to open file %s\n", file_path);
		return false;
	}
	fseek(file, 0, SEEK_END);
	long size = ftell(file);
	rewind(file);
	char *shader_text = (char *) malloc(size + 1);
	fread(shader_text, size, 1, file);
	fclose(file);
	load_shader_src(shader_text, shader);
	free(shader_text);
	return true;
}

GLuint load_shaders(const char *vert_path, const char *frag_path)
{
	GLuint vert_shader = glCreateShader(GL_VERTEX_SHADER);
	GLuint frag_shader = glCreateShader(GL_FRAGMENT_SHADER);

	if (!load_shader_file(vert_path, vert_shader)) {
		fprintf(stderr, "ERROR: Couldn't find file %s\n", vert_path);
	}
	if (!load_shader_file(frag_path, frag_shader)) {
		fprintf(stderr, "ERROR: Couldn't find file %s\n", frag_path);
	}
	glCompileShader(vert_shader);
	glCompileShader(frag_shader);

	GLint success;
	glGetShaderiv(vert_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char log[1024];
		glGetShaderInfoLog(vert_shader, 1024, NULL, log);
		fprintf(stderr, "ERROR: %s failed: %s\n", vert_path, log);
	}
	glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char log[1024];
		glGetShaderInfoLog(frag_shader, 1024, NULL, log);
		fprintf(stderr, "ERROR: %s failed: %s\n", frag_path, log);
	}

	GLuint program = glCreateProgram();
	glAttachShader(program, vert_shader);
	glAttachShader(program, frag_shader);
	glLinkProgram(program);
	glGetProgramiv(program, GL_COMPILE_STATUS, &success);
	if (!success) {
		char log[1024];
		glGetProgramInfoLog(program, 1024, NULL, log);
		fprintf(stderr, "ERROR: The program for %s and %s failed: %s\n", vert_path, frag_path, log);
		glDeleteProgram(program);
	}

	glDeleteShader(vert_shader);
	glDeleteShader(frag_shader);

	return program;
}
