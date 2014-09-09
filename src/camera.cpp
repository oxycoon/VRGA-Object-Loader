#include "camera.h"

#include <iostream>

Camera::Camera()
{
    position_ = glm::vec3(0.0f, 0.0f, -5.0f);
    matrix_ = glm::mat4();
    moveVector_ = glm::vec3();
    matrix_ = glm::translate(matrix_, position_);
    //    matrix_ = glm::rotate(matrix_, 45.0f, glm::vec3(1.0f, 0.0f, 0.0f));
}

void Camera::update()
{
    matrix_ = glm::translate(matrix_, moveVector_);
    //matrix_ = glm::rotate(matrix_, 0.05f, glm::vec3(0.0f, 1.0f, 0.0f));
    //zoomOut();
    moveVector_ = glm::vec3();
}

void Camera::moveRight()
{
    moveVector_ += glm::vec3(-0.10f, 0.0f, 0.0f);
}
void Camera::moveLeft()
{
    moveVector_ += glm::vec3(0.10f, 0.0f, 0.0f);
}
void Camera::moveUp()
{
    moveVector_ += glm::vec3(0.0f, -0.10f, 0.0f);
}
void Camera::moveDown()
{
    moveVector_ += glm::vec3(0.0f, 0.10f, 0.0f);
}
void Camera::moveForward()
{
    //matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, 2.0f));
}

void Camera::zoomIn()
{
    glm::vec3 temp(position_);
    if(glm::length(temp) > 2)
    {
        temp = glm::normalize(temp);
        position_ -= temp;
        matrix_ = glm::translate(matrix_, -temp);
    }

}

void Camera::zoomOut()
{
    glm::vec3 temp(position_);
    if(glm::length(temp) < 10)
    {
        temp = glm::normalize(temp);
        position_ += temp;
        matrix_ = glm::translate(matrix_, temp);
    }

}
void Camera::moveBackward()
{
  matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, -2.0f));
}
