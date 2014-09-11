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
 *  Original source: http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/
 *  Modified to fit.
 */
bool Model::loadModel()
{
    std::vector<glm::vec3> vert;
    std::vector<glm::vec3> norm;
    std::vector<glm::vec2> texCoord; //Not yet implemented.

    FILE * file = fopen(path, "r");
    if( file == NULL )
    {
        printf("Impossible to open the file !\n");
        return false;
    }

    while( 1 )
    {
        char lineHeader[128];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break; // EOF = End Of File. Quit the loop.

        if ( strcmp( lineHeader, "v" ) == 0 )
        {
            glm::vec3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
            vert.push_back(vertex);
        }
        else if ( strcmp( lineHeader, "vt" ) == 0 )
        {
            glm::vec2 uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y );
            texCoord.push_back(uv);
        }
        else if ( strcmp( lineHeader, "vn" ) == 0 )
        {
            glm::vec3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
            norm.push_back(normal);
        }else if ( strcmp( lineHeader, "f" ) == 0 )
        {
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
            if (matches != 9)
            {
                printf("File can't be read by our simple parser : ( Try exporting with other options\n");
                return false;
            }
            vertexIndex_.push_back(vertexIndex[0]);
            vertexIndex_.push_back(vertexIndex[1]);
            vertexIndex_.push_back(vertexIndex[2]);
            uvIndex_    .push_back(uvIndex[0]);
            uvIndex_    .push_back(uvIndex[1]);
            uvIndex_    .push_back(uvIndex[2]);
            normalIndex_.push_back(normalIndex[0]);
            normalIndex_.push_back(normalIndex[1]);
            normalIndex_.push_back(normalIndex[2]);
        }

    }

//    std::ifstream file(path, std::ios::in);
//    if(!file)
//    {
//        std::cerr << "Can't open " << path << std::endl;
//        return false;
//    }

//    std::string line;
//    while(std::getline(file, line))
//    {
//        if(line.substr(0,2) == "v ")
//        {
//            std::istringstream s(line.substr(2));
//            GLfloat x, y, z; s >> x; s >> y; s >> z;
//            glm::vec3 temp(x,y,z);
//            vert.push_back(temp);
//        }
//        else if(line.substr(0,2) == "f ")
//        {
//            std::string vertex1, vertex2, vertex3;
//            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
//            int matches = std::fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
//            if (matches != 9){
//                printf("File can't be read by our simple parser : ( Try exporting with other options\n");
//                return false;
//            }
//            vertexIndex_.push_back(vertexIndex[0]);
//            vertexIndex_.push_back(vertexIndex[1]);
//            vertexIndex_.push_back(vertexIndex[2]);
//            uvIndex_    .push_back(uvIndex[0]);
//            uvIndex_    .push_back(uvIndex[1]);
//            uvIndex_    .push_back(uvIndex[2]);
//            normalIndex_.push_back(normalIndex[0]);
//            normalIndex_.push_back(normalIndex[1]);
//            normalIndex_.push_back(normalIndex[2]);

//            std::stringstream ss(line.substr(2,line.length()));
//            std::string temp;
//            while(ss >> temp)
//            {
//                std::istringstream s(temp);
//                std::string vertInd, uvInd, normInd;
//                std::getline(s, vertInd, '/');
//                std::getline(s, uvInd, '/');
//                std::getline(s, normInd, ' ');

//                if(uvInd == "")
//                    uvIndex_.push_back(0);
//                else
//                    uvIndex_.push_back(std::stoi(uvInd)-1);
//                if(normInd != "")
//                    normalIndex_.push_back(std::stoi(normInd)-1);

//                vertexIndex_.push_back(std::stoi(vertInd)-1);


//            }
//        }
//        else if(line.substr(0,3) == "vn ")
//        {
//            std::istringstream s(line.substr(3));
//            GLfloat x, y, z; s >> x; s >> y; s >> z;
//            glm::vec3 temp(x,y,z);
//            norm.push_back(temp);
//        }
//        else if(line.substr(0,3) == "vt ")
//        {
//            //TODO: Texture coordinates
//        }
//        else if(line[0] == '#'){}
//        else {}
//    }

    if(vertexIndex_.size() == normalIndex_.size())
    {
        for(unsigned int i = 0; i < vertexIndex_.size(); i++)
        {
            glm::vec3 tempVert = vert[vertexIndex_[i]-1];
            glm::vec3 tempNorm = norm[normalIndex_[i]-1];
            //glm::vec2 tempUV = vert[uvIndex_[i]];

            Vertex temp = {tempVert, glm::vec3(0.7f, 0.7f, 0.2f), tempNorm};

            vertices_.push_back(temp);
        }
    }
    else
    {
        std::cout << "Vertex index amount does not match normal index amount, implement manual calculation!" << std::endl;
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
