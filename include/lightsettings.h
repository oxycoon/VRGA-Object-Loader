#ifndef LIGHTSETTINGS_H
#define LIGHTSETTINGS_H

#include <glm/glm.hpp>

/**
 * @brief lightsettings.h
 *
 *  global settings header for lighting.
 */
const static glm::vec3 lightPosition    = glm::vec3(10.0f, 20.0f, 40.0f);
const static glm::vec3 lightDirection   = glm::vec3(-10.0f, -20.0f, -40.0f);
const static glm::vec3 lightAmbient     = glm::vec3(0.2f, 0.2f, 0.4f);
const static glm::vec3 lightDiffuse     = glm::vec3(0.9f, 0.1f, 0.9f);
const static glm::vec3 lightSpecular    = glm::vec3(0.8f, 0.8f, 0.8f);
const static float lightCutoff          = 30.0f;
const static float lightCosCutoff       = 0.52f;
const static float lightSpotExponent    = 0.02f;
//Attenuation variables received from: http://www.ogre3d.org/tikiwiki/tiki-index.php?page=-Point+Light+Attenuation
const static float lightAttConst        = 1.0f;
const static float lightAttLin          = 0.0045f;
const static float lightAttQuad         = 0.00075f;

const static glm::vec3 materialEmission = glm::vec3(0.2f, 0.2f, 0.2f);
const static glm::vec3 materialAmbient  = glm::vec3(0.3f, 0.3f, 0.3f);
const static glm::vec3 materialDiffuse  = glm::vec3(0.7f, 0.7f, 0.2f);
const static glm::vec3 materialSpecular = glm::vec3(0.6f, 0.6f, 0.6f);
const static float materialShininess    = 8.0f;


#endif // LIGHTSETTINGS_H
