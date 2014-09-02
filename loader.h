#ifndef LOADER_H
#define LOADER_H

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

class Loader
{
public:
    Loader();

    void load(const char *path, std::vector<Vertex> &verticies, std::vector<GLushort> &elements);
    void load(const char *path); //test function
};

#endif // LOADER_H
