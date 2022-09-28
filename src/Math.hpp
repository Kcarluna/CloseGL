#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

glm::mat4 transform(float x, float y, float z);
glm::mat4 model_matrix(float angle, float x, float y, float z);
glm::mat4 view_matrix(float x, float y, float z);
glm::mat4 camera_matrix(float radius);
glm::mat4 interactable_camera_matrix(const glm::vec3 &cameraPos, const glm::vec3 &cameraFront, const glm::vec3 &cameraUp);
glm::mat4 projection_matrix(float angle, float x, float y, float z);
