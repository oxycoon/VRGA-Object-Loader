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
    lookAt_ = glm::vec3();
    matrix_ = glm::translate(matrix_, position_);
    //    matrix_ = glm::rotate(matrix_, 45.0f, glm::vec3(1.0f, 0.0f, 0.0f));
}

glm::mat4 Camera::getMatrix()
{
    return matrix_;
}

void Camera::setLookAt(glm::vec3 newLookAt)
{
    lookAt_ = newLookAt;
}

void Camera::setPosition(glm::vec3 newPos)
{
    glm::vec3 translate = position_ - newPos;
    matrix_ = glm::translate(matrix_, translate);
    position_ = newPos;
    //position_ = newPos;
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

    std::cout << "---------------------------" << std::endl;
    std::cout << matrix_[0][0] << "," << matrix_[0][1] << "," << matrix_[0][2] << "," << matrix_[0][3] << std::endl;
    std::cout << matrix_[1][0] << "," << matrix_[1][1] << "," << matrix_[1][2] << "," << matrix_[1][3] << std::endl;
    std::cout << matrix_[2][0] << "," << matrix_[2][1] << "," << matrix_[2][2] << "," << matrix_[2][3] << std::endl;
    std::cout << matrix_[3][0] << "," << matrix_[3][1] << "," << matrix_[3][2] << "," << matrix_[3][3] << std::endl;


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
    //moveVector_ += glm::vec3(0.0f, 0.0f, 1.0f);
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
    //moveVector_ -= glm::vec3(0.0f, 0.0f, 1.0f);
}

//void Camera::rotateCamera(float pitch, float yaw)
//{
//    pitch_ += pitch;
//    yaw_ += yaw;
//}

void Camera::rotateCamera(float angles, glm::vec3 rotationAxis)
{
    rotation_ = glm::rotate(rotation_, angles, rotationAxis);
}

void Camera::moveBackward()
{
  matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, -2.0f));
}
