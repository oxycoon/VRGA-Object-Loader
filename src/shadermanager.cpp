#include "shadermanager.h"

#include <iostream>

ShaderManager::ShaderManager()
{
    //index_ = 0;

    shaderActive_ = false;
}

void ShaderManager::cycleShader()
{
    shaderList_[index_].disable();
    index_++;
    if(index_ >= shaderList_.size())
    {
        index_ = 0;
    }
    shaderList_[index_].enable();
    std::cout << "Active shader: " << shaderList_[index_].getName() << std::endl;
}

void ShaderManager::loadShader(char* path)
{
    Shader temp;
    temp.initShader(path);
    shaderList_.push_back(temp);

    if(!shaderActive_)
    {
        temp.enable();
        shaderActive_ = true;
    }
}

void ShaderManager::activeShader(int index)
{
    if(!index >= shaderList_.size())
    {
        shaderList_[index_].disable();
        shaderList_[index].enable();
        index_ = index;
    }
}

GLuint ShaderManager::getActiveProg()
{
    return shaderList_[index_].getProg();
}
