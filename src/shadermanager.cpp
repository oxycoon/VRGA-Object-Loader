#include "shadermanager.h"

#include <iostream>

ShaderManager::ShaderManager()
{
    //index_ = 0;

    shader_active_ = false;
}

void ShaderManager::cycleShader()
{
    shader_list_[index_].disable();
    index_++;
    if(index_ >= shader_list_.size())
    {
        index_ = 0;
    }
    shader_list_[index_].enable();
    std::cout << "Active shader: " << shader_list_[index_].getName() << std::endl;
}

void ShaderManager::loadShader(char* path)
{
    Shader temp;
    temp.initShader(path);
    shader_list_.push_back(temp);

    if(!shader_active_)
    {
        temp.enable();
        shader_active_ = true;
    }
}

void ShaderManager::activeShader(int index)
{
    if(!index >= shader_list_.size())
    {
        shader_list_[index_].disable();
        shader_list_[index].enable();
        index_ = index;
    }
}

GLuint ShaderManager::getActiveProg()
{
    return shader_list_[index_].getProg();
}
