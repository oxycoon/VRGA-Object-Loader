#ifndef CAMERA_H
#define CAMERA_H

// Ensure we are using opengl's core profile only
#define GL3_PROTOTYPES 1
// Make sure we have glext
#define GL_GLEXT_PROTOTYPES 1

#include <GL/gl.h>
#include <GL/glext.h>

#include "SDL.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define PIOVER180 0.0174532925199

class Camera
{
public:
    Camera();

    glm::mat4 getMatrix(){return matrix_;}

    void update();

    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();
    void moveBackward();
    void moveForward();
    void zoomIn();
    void zoomOut();
    void rotateCamera(float angles, glm::vec3 rotationAxis);

private:
    glm::mat4 matrix_;
    glm::mat4 rotation_;
    glm::vec3 position_;

    glm::vec3 moveVector_;

};

#endif // CAMERA_H
