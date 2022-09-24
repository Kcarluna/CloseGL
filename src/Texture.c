#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "Texture.h"

GLuint generate_texture(const char *file_path)
{
	stbi_set_flip_vertically_on_load(true);
	// NOTE(__LUNA__): Possibly extract this
	int width, height, channels;
	unsigned char *data = stbi_load(file_path, &width, &height, &channels, 0);
	if (!data) {
		fprintf(stderr, "ERROR: Failed to load texture at %s\n", file_path);
	}

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// NOTE(__LUNA__): Deduce file type | Maybe regex would be the move here
	size_t len = strlen(file_path);
	const char file_type[] = {file_path[len - 3], file_path[len - 2], file_path[len - 1], '\0'};

	// NOTE(__LUNA__): This one hurt my brain
	if (!strcmp(file_type, "jpg")) {
		// NOTE(__LUNA__): Set texture parameters... need more research
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// NOTE(__LUNA__): First 0 is the mipmap level
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	} else if (!strcmp(file_type, "png")) {
		// NOTE(__LUNA__): Set texture parameters... need more research
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// NOTE(__LUNA__): Only difference between .jpg and .png is RGBA
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);

	return texture;
}
