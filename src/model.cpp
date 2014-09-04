#include "model.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stddef.h>
#include <cmath>

Model::Model()
{
    path = "";
    matrix_ = glm::mat4();
    hide = false;
}

Model::Model(char *path) : path(path)
{
    matrix_ = glm::mat4();
    hide = false;
}

/**
 * @brief Model::toggleHide
 *
 *  Toggles if this object is to be drawn or not.
 */
void Model::toggleHide()
{
    hide ? hide = false : hide = true;
}

void Model::init()
{
    //If there's no model to load or load fails, model becomes box
    if(!loadModel())
    {

    }
    initBuffer();

}

void Model::render()
{
//    if(!hide)
//    {
        glPushMatrix();
        glMultMatrixf(glm::value_ptr(matrix_));

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);


        glBindBuffer(GL_ARRAY_BUFFER, idVBO_);
        //glBindBuffer(GL_ARRAY_BUFFER, idNBO_);
        glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
        glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, color));
        glVertexAttribPointer((GLuint)2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

        glDrawArrays(GL_TRIANGLES, 0, vertices_.size());

        glDisableVertexAttribArray(2);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(0);
        glPopMatrix();
    //}
}

void Model::update()
{

}

/**
 * @brief Model::loadModel
 *
 *  Original source: http://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Tutorial_Load_OBJ
 *  Modified to fit.
 */
bool Model::loadModel()
{
    std::vector<glm::vec3> vert;
    std::vector<glm::vec3> norm;
    std::vector<glm::vec2> texCoord; //Not positionyet implemented.

    std::ifstream file(path, std::ios::in);
    if(!file)
    {
        std::cerr << "Can't open " << path << std::endl;
        return false;
    }

    std::string line;
    while(std::getline(file, line))
    {
        if(line.substr(0,2) == "v ")
        {
            std::istringstream s(line.substr(2));
            GLfloat x, y, z; s >> x; s >> y; s >> z;
            glm::vec3 temp(x,y,z);
            vert.push_back(temp);
        }
        else if(line.substr(0,2) == "f ")
        {
            std::stringstream ss(line.substr(2,line.length()));
            std::string temp;
            while(ss >> temp)
            {
                std::istringstream s(temp);
                std::string vertInd, uvInd, normInd;
                std::getline(s, vertInd, '/');
                std::getline(s, uvInd, '/');
                std::getline(s, normInd, ' ');

                vertexIndex_.push_back(std::stoi(vertInd)-1);
                uvIndex_.push_back(std::stoi(uvInd)-1);
                normalIndex_.push_back(std::stoi(normInd)-1);
            }
        }
        else if(line.substr(0,3) == "vn ")
        {
            std::istringstream s(line.substr(3));
            GLfloat x, y, z; s >> x; s >> y; s >> z;
            glm::vec3 temp(x,y,z);
            norm.push_back(temp);
        }
        else if(line.substr(0,3) == "vt ")
        {
            //TODO: Texture coordinates
        }
        else if(line[0] == '#'){}
        else {}
    }

    if(vertexIndex_.size() == normalIndex_.size())
    {
        for(unsigned int i = 0; i < vertexIndex_.size(); i++)
        {
            glm::vec3 tempVert = vert[vertexIndex_[i]];
            glm::vec3 tempNorm = vert[normalIndex_[i]];
            //glm::vec2 tempUV = vert[uvIndex_[i]];

            Vertex temp = {tempVert, glm::vec3(0.7f, 0.7f, 0.2f), tempNorm};

            vertices_.push_back(temp);
        }
    }
    else
    {
        std::cout << "Not vertex index amount does not match normal index amount, implement manual calculation!" << std::endl;
        return false;
    }

    return true;
}

void Model::initBuffer()
{
    glGenBuffers(1, &idVBO_);
    glBindBuffer(GL_ARRAY_BUFFER, idVBO_);
    glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof (Vertex), vertices_.data(), GL_STATIC_DRAW);


//    glGenBuffers(1, &idNBO_);
//    glBindBuffer(GL_ARRAY_BUFFER, idNBO_);
//    glBufferData(GL_ARRAY_BUFFER, normalIndex_.size() * sizeof(glm::vec3), &vertices_.front(), GL_STATIC_DRAW);
}
