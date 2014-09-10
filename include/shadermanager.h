#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include <vector>

#include <GL/gl.h>
#include <GL/glext.h>

#include "shader.h"

class ShaderManager
{
public:
    ShaderManager();

    void cycleShader();
    void loadShader(char* path);
    void activeShader(int index);

    GLuint getActiveProg();

private:
    std::vector<Shader> shaderList_;
    int index_;
    bool shaderActive_;
};

#endif // SHADERMANAGER_H
