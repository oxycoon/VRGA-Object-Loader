#include "camera.h"

#include <iostream>
#include <GL/glu.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera()
{
    position_ = glm::vec3(0.0f, 0.0f, -5.0f);
    matrix_ = glm::mat4();
    rotation_ = glm::mat4();
    moveVector_ = glm::vec3();
    upVector_ = glm::vec3(0.0f, 1.0f, 0.0f);
    rightVector_ = glm::vec3(1.0f, 0.0f, 0.0f);
    lookAt_ = glm::vec3(0.0f, 0.0f, 0.0f);
}

glm::mat4 Camera::getMatrix()
{
    return matrix_;
}

glm::mat4 Camera::getViewMatrix()
{
    return view_;
}

glm::vec3 Camera::getPosition()
{
    return position_;
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
}

void Camera::setProjection(glm::mat4 projection)
{
    projection_ = projection;
}

void Camera::init()
{
    matrix_ = glm::translate(matrix_, position_);
}



void Camera::update()
{
    position_ += moveVector_;

    view_ = glm::lookAt(lookAt_, position_, upVector_);
    matrix_ = glm::translate(matrix_, moveVector_);
    matrix_ *= rotation_;


//    std::cout << "---------------------------" << std::endl;
//    std::cout << matrix_[0][0] << "," << matrix_[0][1] << "," << matrix_[0][2] << "," << matrix_[0][3] << std::endl;
//    std::cout << matrix_[1][0] << "," << matrix_[1][1] << "," << matrix_[1][2] << "," << matrix_[1][3] << std::endl;
//    std::cout << matrix_[2][0] << "," << matrix_[2][1] << "," << matrix_[2][2] << "," << matrix_[2][3] << std::endl;
//    std::cout << matrix_[3][0] << "," << matrix_[3][1] << "," << matrix_[3][2] << "," << matrix_[3][3] << std::endl;
//    std::cout << position_[0] << "," << position_[1] << "," << position_[2] << std::endl;
    moveVector_ = glm::vec3();
    rotation_ = glm::mat4();
}

void Camera::moveRight()
{
    //moveVector_ += glm::vec3(-0.10f, 0.0f, 0.0f);
    glm::vec3 temp = glm::cross(position_, upVector_);
    temp  = glm::normalize(temp);
    temp *= -0.2f;

    moveVector_ += temp;
}
void Camera::moveLeft()
{
    //moveVector_ += glm::vec3(0.10f, 0.0f, 0.0f);
    glm::vec3 temp = glm::cross(position_, upVector_);
    temp  = glm::normalize(temp);
    temp *= -0.2f;

    moveVector_ -= temp;
}
void Camera::moveUp()
{
//    moveVector_ += glm::vec3(0.0f, -0.10f, 0.0f);
    glm::vec3 temp = glm::cross(position_, rightVector_);
    temp  = glm::normalize(temp);
    temp *= -0.1f;

    moveVector_ -= temp;
}
void Camera::moveDown()
{
//    moveVector_ += glm::vec3(0.0f, 0.10f, 0.0f);

    //moveVector_ += glm::vec3(0.10f, 0.0f, 0.0f);
    glm::vec3 temp = glm::cross(position_, rightVector_);
    temp  = glm::normalize(temp);
    temp *= -0.1f;

    moveVector_ += temp;
}
void Camera::moveForward()
{
    //matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, 2.0f));
}

void Camera::zoomIn()
{
    //glm::vec3 temp(matrix_[3][0], matrix_[3][1],matrix_[3][2]);
    glm::vec3 temp(position_);
    if(glm::length(temp) > 2)
    {
        temp = glm::normalize(temp);
        //std::cout << temp[0] << "," << temp[1] << "," << temp[2] << std::endl;

        moveVector_ -= temp;
        //position_ -= temp;
        //matrix_ = glm::translate(matrix_, -temp);
    }
//    if(zoom_ > 0.5)
//    {
//       zoom_ -= 0.02;
//    }
    //moveVector_ += glm::vec3(0.0f, 0.0f, 1.0f);
}

void Camera::zoomOut()
{
//    if(zoom_ < 1.5)
//    {
//       zoom_ += 0.02;
//    }
    //glm::vec3 temp(matrix_[3][0], matrix_[3][1],matrix_[3][2]);
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

void Camera::rotateCamera(glm::vec3 eulerAngles)
{
    quaterion_ = glm::quat(eulerAngles);
    rotation_ = glm::toMat4(quaterion_);
}

void Camera::moveBackward()
{
  matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, -2.0f));
}
