#ifndef SHADER_H
#define SHADER_H

#include <string>

// Ensure we are using opengl's core profile only
#define GL3_PROTOTYPES 1
// Make sure we have glext
#define GL_GLEXT_PROTOTYPES 1

#include <GL/gl.h>
#include <GL/glext.h>

enum ShaderType {V_SHADER, F_SHADER};

class Shader
{
public:
    Shader();
    ~Shader();

    void enable();
    void disable();
    GLuint getProg();
    std::string getName();

    bool initShader(char* path);

private:
    GLuint vs_, fs_, prog_;
    GLchar *vs_source_, *fs_source_;
    std::string name_;

    int shaderSize(char *path, ShaderType st);
    int readShader(char *path, ShaderType st, char* shaderSource, int size);
};

#endif // SHADER_H
