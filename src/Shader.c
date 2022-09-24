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
	char log[1024];
	glGetShaderiv(vert_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vert_shader, 1024, NULL, log);
		fprintf(stderr, "%s at (%s)\n", log, vert_path);
	}
	glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(frag_shader, 1024, NULL, log);
		fprintf(stderr, "%s at (%s)\n", log, frag_path);
	}

	GLuint program = glCreateProgram();
	glAttachShader(program, vert_shader);
	glAttachShader(program, frag_shader);
	glLinkProgram(program);
	glGetProgramiv(program, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 1024, NULL, log);
		fprintf(stderr, "%s at (%s and %s)\n", log, vert_path, frag_path);
	}

	glDeleteShader(vert_shader);
	glDeleteShader(frag_shader);

	return program;
}
