#include "Math.hpp"

// NOTE(__LUNA__): Here's where we switch to cpp.... This is a cpp only lib. Must port all code over to cpp
glm::mat4 transform()
{
	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));

	return trans;
}
