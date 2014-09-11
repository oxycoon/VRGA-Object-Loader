#ifndef LIGHTSETTINGS_H
#define LIGHTSETTINGS_H

#include <glm/glm.hpp>

/**
 * @brief lightsettings.h
 *
 *  global settings header for lighting.
 */
const static glm::vec3 lightPosition    = glm::vec3(10.0f, 30.0, 40.0f);
const static glm::vec3 lightDirection   = glm::vec3(-10.0f, -2.0f, -5.0f);
const static glm::vec3 lightAmbient     = glm::vec3(1.0f, 1.0f, 0.8f);
const static glm::vec3 lightDiffuse     = glm::vec3(0.6f, 0.2f, 0.8f);
const static glm::vec3 lightSpecular    = glm::vec3(0.8f, 0.8f, 0.8f);



#endif // LIGHTSETTINGS_H
