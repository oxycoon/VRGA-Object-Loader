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
}

Model::Model(char *path)
{
    this->path = path;
}

void Model::init()
{
    //If there's no model to load or load fails, model becomes box
    if(!loadModel())
    {

    }


}

void Model::render()
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
            Vertex v = {{ x, y, z }, { 1.0f, 1.0f, 1.0f }, {0.0f, 0.0f, 0.0f}};
            vertices.push_back(v);
            std::cout << "Added point: " << x << ", " << y << ", " << z << std::endl;
        }
        else if(line.substr(0,2) == "f ")
        {
            std::istringstream s(line.substr(2));
            GLushort a, b, c;
            s >> a; s >> b; s >> c;
            elements.push_back(a);
            elements.push_back(b);
            elements.push_back(c);
        }
        else if(line[0] == '#'){}
        else {}

        for(int i = 0; i < elements.size(); i+= 3)
        {
            GLushort a = elements[i];
            GLushort b = elements[i+1];
            GLushort c = elements[i+2];

            //TODO: optimalize
            glm::vec3 vec1 = glm::vec3(vertices[b].position[0] - vertices[a].position[0],
                                    vertices[b].position[1] - vertices[a].position[1],
                                    vertices[b].position[2] - vertices[a].position[2]);
            glm::vec3 vec2 = glm::vec3(vertices[c].position[0] - vertices[a].position[0],
                                    vertices[c].position[1] - vertices[a].position[1],
                                    vertices[c].position[2] - vertices[a].position[2]);

            glm::vec3 normal = glm::normalize(glm::cross(vec1, vec2));
            vertices[a].normal[0] = vertices[b].normal[0] = vertices[c].normal[0] = normal.x;
            vertices[a].normal[1] = vertices[b].normal[1] = vertices[c].normal[1] = normal.y;
            vertices[a].normal[2] = vertices[b].normal[2] = vertices[c].normal[2] = normal.z;
            //ENDTODO
        }

    }
    return true;
}
