#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>

class Light
{
public:
    Light(glm::vec3 position,
            glm::vec3 direction,
            glm::vec3 ambient,
            glm::vec3 diffuse,
            glm::vec3 specular,
            bool isSpot,
            bool isOmniDirectional);

    glm::vec3 getPosition();
    glm::vec3 getDirection();
    glm::vec3 getAmbient();
    glm::vec3 getDiffuse();
    glm::vec3 getSpecular();
    bool isSpot();
    bool isOmniDirectional();

private:
    glm::vec3 position_;
    glm::vec3 direction_;
    glm::vec3 ambient_;
    glm::vec3 diffuse_;
    glm::vec3 specular_;

    bool is_spot_;
    bool is_omni_directional_;
};

#endif // LIGHT_H
