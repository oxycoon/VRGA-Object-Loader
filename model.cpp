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

}

void Model::render()
{

}

void Model::loadModel()
{
    std::ifstream file(path, std::ios::in);
    if(!file)
    {
        std::cerr << "Can't open " << path << std::endl;
        std::exit(1);
    }


    //file = filetobuf(path);

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



    }
}
