#include "camera.h"

Camera::Camera()
{
}

void Camera::moveRight()
{
  matrix_ = glm::translate(matrix_, glm::vec3(-2.0f, 0.0f, 0.0f));
}
void Camera::moveLeft()
{
  matrix_ = glm::translate(matrix_, glm::vec3(2.0f, 0.0f, 0.0f));
}
void Camera::moveUp()
{
  matrix_ = glm::translate(matrix_, glm::vec3(0.0f, -2.0f, 0.0f));
}
void Camera::moveDown()
{
  matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 2.0f, 0.0f));
}
void Camera::moveForward()
{
  matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, 2.0f));
}
void Camera::moveBackward()
{
  matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, -2.0f));
}
