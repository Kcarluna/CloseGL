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
