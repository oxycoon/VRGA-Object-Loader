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

bool Model::init()
{
    //If there's no model to load or load fails, model becomes box
    if(!loadModel())
    {
        return false;
    }
    initBuffer();

    return true;
}

void Model::render()
{
    if(!hide)
    {
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
    }
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
            //printf("Vertex: %f,%f,%f\n", vertex.x, vertex.y, vertex.z);
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
            //printf("Normal: %f,%f,%f\n", normal.x, normal.y, normal.z);
            norm.push_back(normal);
        }else if ( strcmp( lineHeader, "f" ) == 0 )
        {
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
            if (matches != 9)
            {
                printf("File can't be read by our simple parser : ( Try exporting with other options\n");
                return false;
            }
            vertex_index_.push_back(vertexIndex[0]);
            vertex_index_.push_back(vertexIndex[1]);
            vertex_index_.push_back(vertexIndex[2]);
            uv_index_.push_back(uvIndex[0]);
            uv_index_.push_back(uvIndex[1]);
            uv_index_.push_back(uvIndex[2]);
            normal_index_.push_back(normalIndex[0]);
            normal_index_.push_back(normalIndex[1]);
            normal_index_.push_back(normalIndex[2]);
        }

    }

    if(vertex_index_.size() == normal_index_.size())
    {
        for(unsigned int i = 0; i < vertex_index_.size(); i++)
        {
            glm::vec3 tempVert = vert[vertex_index_[i]-1];
            glm::vec3 tempNorm = norm[normal_index_[i]-1];
            //glm::vec2 tempUV = vert[uv_index_[i]];

            Vertex temp = {tempVert, glm::vec3(0.7f, 0.7f, 0.2f), tempNorm};

//            printf("Vertex created: (%f,%f,%f), (%f,%f,%f), (%f,%f,%f)\n",
//                   temp.position.x, temp.position.y, temp.position.z,
//                   temp.color.x, temp.color.y, temp.color.z,
//                   temp.normal.x, temp.normal.y, temp.normal.z);

            vertices_.push_back(temp);
        }
    }
    //EXPERIMENTAL AND UNTESTED
    else
    {
        for(int i = 0; i < vertex_index_.size(); i+=3)
        {
            GLuint a = vertex_index_[i-1];
            GLuint b = vertex_index_[i];
            GLuint c = vertex_index_[i+1];

            glm::vec3 normal = glm::normalize(glm::cross(
                    glm::vec3(vert[b]) - glm::vec3(vert[a]),
                    glm::vec3(vert[c]) - glm::vec3(vert[a])));

            Vertex temp1 = {vert[a], glm::vec3(0.7f, 0.7f, 0.2f), normal};
            Vertex temp2 = {vert[b], glm::vec3(0.7f, 0.7f, 0.2f), normal};
            Vertex temp3 = {vert[c], glm::vec3(0.7f, 0.7f, 0.2f), normal};
            vertices_.push_back(temp1);
            vertices_.push_back(temp2);
            vertices_.push_back(temp3);
        }
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
//    glBufferData(GL_ARRAY_BUFFER, normal_index_.size() * sizeof(glm::vec3), &vertices_.front(), GL_STATIC_DRAW);
}
