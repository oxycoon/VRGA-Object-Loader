#ifndef MODEL_H
#define MODEL_H

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

struct Vertex
{
  GLfloat position[3];
  GLfloat color[3];
  GLfloat normal[3];
};

class Model
{
public:
    Model();
    Model(char* path);

    std::vector<Vertex> getVertics(){return vertices;}
    void setPath(char* newPath){path = newPath;}

    void init();
    void render();
    void update();



protected:
    glm::mat4 matrix_;

private:
    std::vector<Vertex> vertices;
    std::vector<GLushort> elements;
    GLuint id;

    char* path;

    bool loadModel();

};

#endif // MODEL_H
