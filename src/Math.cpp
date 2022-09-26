#include <GLFW/glfw3.h>
#include "Math.hpp"

// NOTE(__LUNA__): Here's where we switch to cpp.... This is a cpp only lib. Must port all code over to cpp
glm::mat4 transform(float x, float y, float z)
{
	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::translate(trans, glm::vec3(x, y, z));
	trans = glm::scale(trans, glm::vec3(sin(glfwGetTime()), sin(glfwGetTime()), sin(glfwGetTime())));
	trans = glm::rotate(trans, (float) glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

	return trans;
}

glm::mat4 model_matrix(float angle, float x, float y, float z)
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(x, y, z));
	model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

	return model;
}

glm::mat4 view_matrix(float x, float y, float z)
{
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(x, y, z));

	return view;
}

glm::mat4 projection_matrix(float angle, float x, float y, float z)
{
	glm::mat4 proj = glm::mat4(1.0f);
	proj = glm::perspective(glm::radians(angle), x, y, z);

	return proj;
}
