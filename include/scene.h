#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <string>
#include <stddef.h>
#include <cmath>
#include <memory>
#include <vector>

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

class Model;
//class Camera;

class Scene
{
public:
    Scene();

    void render();
    void update();
    void init();

    void addModelToScene(char* path);
    void addSceneObject(std::shared_ptr<Model> newChild);
    void removeSceneObject(const std::shared_ptr<Model> child);
    void toggleSceneObject(const std::shared_ptr<Model> child);

private:
    std::vector<std::shared_ptr<Model>> sceneObjects_;
    std::vector<std::shared_ptr<Model>> newChildren_;

    glm::mat4 world_;
    glm::mat4 projection_;
    glm::mat4 view_;

    GLuint vao_, vbo_[0];
};

#endif // SCENE_H
