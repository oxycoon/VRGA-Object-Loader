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

Model::Model(char *path)
{
    this->path = path;
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


}

void Model::render()
{
    if(!hide)
    {
        glPushMatrix();
        glMultMatrixf(glm::value_ptr(matrix_));









        glDrawArrays(GL_TRIANGLES, 0, vertices_.size());





        glPopMatrix();
    }
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
//    std::vector<GLuint> vertIndex, uvIndex, normIndex;
//    std::vector<glm::vec3> vert, norm;
//    std::vector<glm::vec2> uv;

//    FILE * file = std::fopen(path, "r");
//    if(file == NULL)
//    {
//        printf("Can't open file %s\n", path);
//        return false;
//    }
//    while(1)
//    {
//        char header[128];
//        int res = fscanf(file, "%s", header);
//        if(res = EOF)
//            break;

//        //Vertex
//        if( strcmp(header, "v") == 0)
//        {
//            glm::vec3 vertex;
//            fscanf(file, "%f %f %f\n")
//        }
//        //Texture coordinate
//        else if( strcmp(header, "vt") == 0)
//        {

//        }
//        //Normal
//        else if( strcmp(header, "vn") == 0)
//        {

//        }

//        else if( strcmp(header, "f") == 0)
//        {

//        }
//    }
    std::vector<glm::vec3> vert;
    std::vector<glm::vec3> norm;
    std::vector<glm::vec2> texCoord;
    //std::vector<GLushort> ind;

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
//            Vertex v = {{ x, y, z }, { 1.0f, 1.0f, 1.0f }, {0.0f, 0.0f, 0.0f}};
//            vertices_.push_back(v);
            glm::vec3 temp(x,y,z);
            vert.push_back(temp);
            //std::cout << "Added point: " << x << ", " << y << ", " << z << std::endl;
        }
        else if(line.substr(0,2) == "f ")
        {

            std::istringstream s(line.substr(2));
            GLuint vertex[3], uv[3], normal[3];
            //std::string temp = s.

            s >> vertex[0]; s >> uv[0]; s >> normal[0];
            s >> vertex[1]; s >> uv[1]; s >> normal[1];
            s >> vertex[2]; s >> uv[2]; s >> normal[2];
            vertex[0]--;uv[0]--;normal[0]--;
            vertex[1]--;uv[1]--;normal[1]--;
            vertex[2]--;uv[2]--;normal[2]--;
//            indices_.push_back(vertex);
//            elements_.push_back(vertex);
//            elements_.push_back(uv);
//            elements_.push_back(normal);
        }
        else if(line.substr(0,3) == "vn ")
        {
            std::istringstream s(line.substr(3));
            GLfloat x, y, z; s >> x; s >> y; s >> z;
            glm::vec3 temp(x,y,z);
            norm.push_back(temp);
        }
        else if(line[0] == '#'){}
        else {}
    }
//    //checks if each vertex has an accociated normal
    if(norm.size() == vert.size())
    {
        for(int i = 0; i < vert.size(); i++)
        {
            Vertex v = {vert[i], glm::vec3(1.0f, 0.5f, 1.0f), norm[i]};
            vertices_.push_back(v);
        }
    }
    //calculates normals manually
    else
    {
        for(int i = 0; i < indices_.size(); i+= 3)
        {
            GLushort a = indices_[i];
            GLushort b = indices_[i+1];
            GLushort c = indices_[i+2];

            //TODO: optimalize
            glm::vec3 vec1 = glm::vec3(vertices_[b].position[0] - vertices_[a].position[0],
                                    vertices_[b].position[1] - vertices_[a].position[1],
                                    vertices_[b].position[2] - vertices_[a].position[2]);
            glm::vec3 vec2 = glm::vec3(vertices_[c].position[0] - vertices_[a].position[0],
                                    vertices_[c].position[1] - vertices_[a].position[1],
                                    vertices_[c].position[2] - vertices_[a].position[2]);

            glm::vec3 normal = glm::normalize(glm::cross(vec1, vec2));
            vertices_[a].normal[0] = vertices_[b].normal[0] = vertices_[c].normal[0] = normal.x;
            vertices_[a].normal[1] = vertices_[b].normal[1] = vertices_[c].normal[1] = normal.y;
            vertices_[a].normal[2] = vertices_[b].normal[2] = vertices_[c].normal[2] = normal.z;
            //ENDTODO
        }
    }

    //glEnableVertexAttribArray(id);

    return true;
}
