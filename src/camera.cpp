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
    move_vector_ = glm::vec3();
    up_vector_ = glm::vec3(0.0f, 1.0f, 0.0f);
    right_vector_ = glm::vec3(1.0f, 0.0f, 0.0f);
    look_at_ = glm::vec3(0.0f, 0.0f, 0.0f);
}

/**
 * @brief Camera::getMatrix
 * @return The camera world matrix
 *
 *  Gets the camera's world matrix.
 */
glm::mat4 Camera::getMatrix()
{
    return matrix_;
}

/**
 * @brief Camera::getViewMatrix
 * @return The camera view matrix.
 *
 *  Gets the camera's viwe matrix.
 */
glm::mat4 Camera::getViewMatrix()
{
    return view_;
}

/**
 * @brief Camera::getPosition
 * @return The camera position
 *
 *  Gets the camera position in the world.
 */
glm::vec3 Camera::getPosition()
{
    return position_;
}

/**
 * @brief Camera::setLookAt
 * @param newLookAt
 *
 *  Sets a new look at for the camera.
 */
void Camera::setLookAt(glm::vec3 newLookAt)
{
    look_at_ = newLookAt;
}

/**
 * @brief Camera::setPosition
 * @param newPos
 *
 *  Sets a new position for the camera
 */
void Camera::setPosition(glm::vec3 newPos)
{
    glm::vec3 translate = position_ - newPos;
    matrix_ = glm::translate(matrix_, translate);
    position_ = newPos;
}

/**
 * @brief Camera::setProjection
 * @param projection
 *
 *  Sets a new projection matrix for the camera.
 */
void Camera::setProjection(glm::mat4 projection)
{
    projection_ = projection;
}

/**
 * @brief Camera::init
 *
 *  Initializes the camera for the first time, putting the camera in
 *  the starting position.
 */
void Camera::init()
{
    matrix_ = glm::translate(matrix_, position_);
}

/**
 * @brief Camera::update
 *
 *  Updates the camera position from the movement vectors and rotation
 *  matrix. Then resets the two for the next update cycle.
 */
void Camera::update()
{
    position_ += move_vector_;

    view_ = glm::lookAt(look_at_, position_, up_vector_);
    matrix_ = glm::translate(matrix_, move_vector_);
    matrix_ *= rotation_;

    move_vector_ = glm::vec3();
    rotation_ = glm::mat4();
}

/**
 * @brief Camera::moveRight
 *
 *  Moves the camera to the right, rotating to the right around
 *  the look at point.
 */
void Camera::moveRight()
{
    glm::vec3 temp = glm::cross(position_, up_vector_);
    temp  = glm::normalize(temp);
    temp *= -0.2f;

    move_vector_ += temp;
}

/**
 * @brief Camera::moveLeft
 *
 *  Moves the camera to the left, rotating to the left around
 *  the look at point.
 */
void Camera::moveLeft()
{
    glm::vec3 temp = glm::cross(position_, up_vector_);
    temp  = glm::normalize(temp);
    temp *= -0.2f;

    move_vector_ -= temp;
}

/**
 * @brief Camera::moveUp
 *
 *  Moves the camera upwards
 */
void Camera::moveUp()
{
    glm::vec3 temp = glm::cross(position_, right_vector_);
    temp  = glm::normalize(temp);
    temp *= -0.1f;

    move_vector_ -= temp;
}

/**
 * @brief Camera::moveDown
 *
 *  Moves the camera downwards
 */
void Camera::moveDown()
{
    glm::vec3 temp = glm::cross(position_, right_vector_);
    temp  = glm::normalize(temp);
    temp *= -0.1f;

    move_vector_ += temp;
}

/**
 * @brief Camera::zoomIn
 *
 *  "Zooms" the camera closer to the object
 */
void Camera::zoomIn()
{
    glm::vec3 temp(position_);
    if(glm::length(temp) > 2)
    {
        temp = glm::normalize(temp);

        move_vector_ -= temp;
    }
}

/**
 * @brief Camera::zoomOut
 *
 *  "Zooms" the camera away from the object
 */
void Camera::zoomOut()
{
    glm::vec3 temp(position_);
    if(glm::length(temp) < 10)
    {
        temp = glm::normalize(temp);
        move_vector_ += temp;
    }
}

/**
 * @brief Camera::rotateCamera
 * @param eulerAngles
 *
 *  Rotates the camera using euler angles and quaterions.
 */
void Camera::rotateCamera(glm::vec3 eulerAngles)
{
    quaterion_ = glm::quat(eulerAngles);
    rotation_ = glm::toMat4(quaterion_);
}
