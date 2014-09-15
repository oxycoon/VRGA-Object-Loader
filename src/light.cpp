#include "light.h"

Light::Light(glm::vec3 position, glm::vec3 direction, glm::vec3 ambient,
             glm::vec3 diffuse, glm::vec3 specular, bool isSpot, bool isOmniDirectional)
    : position_(position), direction_(direction), ambient_(ambient),
      diffuse_(diffuse), specular_(specular), is_spot_(isSpot), is_omni_directional_(isOmniDirectional)
{

}
