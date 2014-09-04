#include "shader.h"

#include <fcntl.h>
#include <iostream>
#include <memory>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <unistd.h>

//#include <sys/types.h>
//#include <sys/stat.h>


#include "util.h"

using namespace std;

Shader::Shader()
{
}

Shader::~Shader()
{

}

void Shader::enable()
{
    glUseProgram(prog_);
}

void Shader::disable()
{
    glUseProgram(0);
}

GLuint Shader::getProg()
{
    return prog_;
}

bool Shader::initShader(char *path)
{
    int vSize, fSize;

    vSize = shaderSize(path, V_SHADER);
    fSize = shaderSize(path, F_SHADER);

    if((vSize == -1) || (fSize == -1))
    {
        cout << "Cannot determine size of shader " << path << endl;
        return false;
    }

    vsSource_ = (GLchar*)malloc(vSize);
    fsSource_ = (GLchar*)malloc(fSize);

    //read our shaders
    if(!readShader(path, V_SHADER, vsSource_, vSize))
    {
        cout << "Cannot read file " << path << ".vert" << std::endl;
        return false;
    }

    if(!readShader(path, F_SHADER, fsSource_, fSize))
    {
        cout << "Cannot read file " << path << ".frag" << std::endl;
        return false;
    }

    GLint vertCompiled, fragCompiled;
    GLint linked;
    int infologLength = 0;
    int charsWritten = 0;
    GLchar *infoLog;

    //Create shader objects
    vs_ = glCreateShader(GL_VERTEX_SHADER);
    fs_ = glCreateShader(GL_FRAGMENT_SHADER);

    const char *vertS = vsSource_;
    const char *fragS = fsSource_;

    //Load shader source
    glShaderSource(vs_, 1, &vertS, 0);
    glShaderSource(fs_, 1, &fragS, 0);

    //Compile and log vertex shader
    glCompileShader(vs_);
    glGetShaderiv(vs_, GL_COMPILE_STATUS, &vertCompiled);
    glGetShaderiv(vs_, GL_INFO_LOG_LENGTH, &infologLength);
    if (infologLength > 0)
    {
        infoLog = (GLchar *)malloc(infologLength);
        if (infoLog == NULL)
        {
            cout << "ERROR: Could not allocate InfoLog buffer" << endl;
            exit(1);
        }
        glGetShaderInfoLog(vs_, infologLength, &charsWritten, infoLog);
        cout << "Shader InfoLog:\n" << infoLog << "\n" << endl;
        free(infoLog);
    }

    //Compile and log fragment shader
    glCompileShader(fs_);
    glGetShaderiv(fs_, GL_COMPILE_STATUS, &fragCompiled);
    glGetShaderiv(fs_, GL_INFO_LOG_LENGTH, &infologLength);
    if (infologLength > 0)
    {
        infoLog = (GLchar *)malloc(infologLength);
        if (infoLog == NULL)
        {
            cout << "ERROR: Could not allocate InfoLog buffer" << endl;
            exit(1);
        }
        glGetShaderInfoLog(fs_, infologLength, &charsWritten, infoLog);
        cout << "Shader InfoLog:\n" << infoLog << "\n" << endl;
        free(infoLog);
    }

    if(!vertCompiled || !fragCompiled)
        return false;

    //Create program and attach the shaders
    prog_ = glCreateProgram();
    glAttachShader(prog_, vs_);
    glAttachShader(prog_, fs_);

//      glBindAttribLocation(prog_, 0, "in_Position");
//      glBindAttribLocation(prog_, 1, "in_Color");

    //Link program and print log
    glLinkProgram(prog_);
    glGetProgramiv(prog_, GL_LINK_STATUS, &linked);
    glGetProgramiv(prog_, GL_INFO_LOG_LENGTH, &infologLength);
    if (infologLength > 0)
    {
        infoLog = (GLchar *)malloc(infologLength);
        if (infoLog == NULL)
        {
            cout << "ERROR: Could not allocate InfoLog buffer" << endl;
            exit(1);
        }
        glGetProgramInfoLog(prog_, infologLength, &charsWritten, infoLog);
        cout << "Program InfoLog:\n" << infoLog << "\n" << endl;
        free(infoLog);
    }

  glBindAttribLocation(prog_, 0, "in_Position");
  glBindAttribLocation(prog_, 1, "in_Color");
  glBindAttribLocation(prog_, 2, "in_Normal");

//    cout << vsSource_ << endl;
//    cout << fsSource_ << endl;

    if (!linked)
        return false;
    return true;
}

int Shader::shaderSize(char *path, ShaderType st)
{
    int fd;
    char name[100];
    int count = -1;

    strcpy(name, path);

    switch(st)
    {
    case V_SHADER:
        strcat(name, ".vert");
        break;
    case F_SHADER:
        strcat(name, ".frag");
        break;
    default:
        cout << "ERROR: unknown shader file type " << endl;
        exit(1);
        break;
    }
    ///USE UNDERSCORE BEFORE open, O_RDONLY, lseek, close (WIN32)
    // Open the file, seek to the end to find its length (WIN32)
    fd = open(name, O_RDONLY);
    if (fd != -1)
    {
        count = lseek(fd, 0, SEEK_END) + 1;
        close(fd);
    }
    return count;
}

int Shader::readShader(char *path, ShaderType st, char *shaderSource, int size)
{
    FILE *fh;
    char name[100];
    int count;

    strcpy(name, path);

    switch(st)
    {
        case V_SHADER:
            strcat(name, ".vert");
            break;
        case F_SHADER:
            strcat(name, ".frag");
            break;
        default:
            cout << "ERROR: unknown shader file type!" << endl;
            exit(1);
            break;
    }


    // Open the file
    fh = fopen(name, "r");
    if (!fh)
      return -1;

    // Get the shader from a file.
    fseek(fh, 0, SEEK_SET);
    count = (int) fread(shaderSource, 1, size, fh);
    shaderSource[count] = '\0';

    if (ferror(fh))
        count = 0;

    fclose(fh);
    return count;

    return count;

}
