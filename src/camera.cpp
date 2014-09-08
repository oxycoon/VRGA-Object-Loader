#include "camera.h"

Camera::Camera()
{
    matrix_ = glm::mat4();
    matrix_ = glm::translate(matrix_, glm::vec3(0.f, 0.f, -5.0f));
//    matrix_ = glm::rotate(matrix_, 45.0f, glm::vec3(1.0f, 0.0f, 0.0f));
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
