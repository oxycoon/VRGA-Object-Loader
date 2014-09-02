#include "loader.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stddef.h>
#include <cmath>


#include "util.h"

Loader::Loader()
{
}

/**
 * @brief Loader::load
 * @param path
 * @param verticies
 * @param normals
 * @param elements
 *
 *  Principle aquired from http://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Tutorial_Load_OBJ
 */
void Loader::load(const char *path, std::vector<Vertex> &verticies, std::vector<GLushort> &elements)
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
            verticies.push_back(v);
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

void Loader::load(const char *path)
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
            Vertex v = {{ x, y, z }, { 1.0f, 1.0f, 1.0f }};

            //std::cout << "Added point: " << x << ", " << y << ", " << z << std::endl;
        }
        else if(line.substr(0,2) == "f ")
        {

        }
        else if(line[0] == '#'){}
        else {}
    }

}

