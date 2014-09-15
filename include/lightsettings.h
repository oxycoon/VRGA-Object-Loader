#ifndef LIGHTSETTINGS_H
#define LIGHTSETTINGS_H

#include <glm/glm.hpp>

/**
 * @brief lightsettings.h
 *
 *  global settings header for lighting.
 */
const static glm::vec3 kLightPosition    = glm::vec3(10.0f, 20.0f, 40.0f);
const static glm::vec3 kLightDirection   = glm::vec3(-10.0f, -20.0f, -40.0f);
const static glm::vec3 kLightAmbient     = glm::vec3(0.2f, 0.2f, 0.4f);
const static glm::vec3 kLightDiffuse     = glm::vec3(0.9f, 0.1f, 0.9f);
const static glm::vec3 kLightSpecular    = glm::vec3(0.8f, 0.8f, 0.8f);
const static float kLightCutoff          = 30.0f;
const static float kLightCosCutoff       = 0.52f;
const static float kLightSpotExponent    = 0.02f;
//Attenuation variables received from: http://www.ogre3d.org/tikiwiki/tiki-index.php?page=-Point+kLight+Attenuation
const static float kLightAttConst        = 1.0f;
const static float kLightAttLin          = 0.0045f;
const static float kLightAttQuad         = 0.00075f;

const static glm::vec3 kMaterialEmission = glm::vec3(0.2f, 0.2f, 0.2f);
const static glm::vec3 kMaterialAmbient  = glm::vec3(0.3f, 0.3f, 0.3f);
const static glm::vec3 kMaterialDiffuse  = glm::vec3(0.7f, 0.7f, 0.2f);
const static glm::vec3 kMaterialSpecular = glm::vec3(0.6f, 0.6f, 0.6f);
const static float kMaterialShininess    = 8.0f;


#endif // LIGHTSETTINGS_H
