#include "camera.h"

#include <iostream>
#include <GL/glu.h>

Camera::Camera()
{
    position_ = glm::vec3(0.0f, 0.0f, -5.0f);
    matrix_ = glm::mat4();
    rotation_ = glm::mat4();
    moveVector_ = glm::vec3();
    upVector_ = glm::vec3(0.0f, 1.0f, 0.0f);
    matrix_ = glm::translate(matrix_, position_);
    //    matrix_ = glm::rotate(matrix_, 45.0f, glm::vec3(1.0f, 0.0f, 0.0f));
}

void Camera::update()
{
//    glm::vec3 centerTarget = position_ - lookAt_;
//    glm::vec3 normalizedCenterTarget = glm::normalize(centerTarget);
//    glm::vec3 normalizedUp = glm::normalize(upVector_);

//    glm::vec3 s = glm::cross(normalizedCenterTarget, normalizedUp);
//    glm::vec3 normalizedS = glm::normalize(s);
//    glm::vec3 u = glm::cross(normalizedS, normalizedCenterTarget);



    matrix_ = glm::translate(matrix_, moveVector_);
    matrix_ *= rotation_;
    //zoomOut();
    position_ += moveVector_;
    moveVector_ = glm::vec3();
    rotation_ = glm::mat4();

    //matrix_ *= glm::mat4(glm::vec4(s, 0.0f), glm::vec4(u, 0.0f), glm::vec4(-normalizedCenterTarget, 0.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
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
        moveVector_ -= temp;
        //position_ -= temp;
        //matrix_ = glm::translate(matrix_, -temp);
    }

}

void Camera::zoomOut()
{
    glm::vec3 temp(position_);
    if(glm::length(temp) < 10)
    {
        temp = glm::normalize(temp);
        moveVector_ += temp;
        //position_ += temp;
        //matrix_ = glm::translate(matrix_, temp);
    }

}

void Camera::rotateCamera(float angles, glm::vec3 rotationAxis)
{
    rotation_ = glm::rotate(rotation_, angles, rotationAxis);
}
void Camera::moveBackward()
{
  matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, -2.0f));
}
