#include "utils/public/lightmanager.h"

Light::Light()
{
    ambient_ = glm::vec3(1.0f);
    diffuse_ = glm::vec3(1.0f);
    specular_ = glm::vec3(1.0f);

    vector_ = glm::vec4(glm::vec3(), 1.0f);
}

Light::Light(glm::vec4 vector)
{
    ambient_ = glm::vec3(1.0f);
    diffuse_ = glm::vec3(1.0f);
    specular_ = glm::vec3(1.0f);

    vector_ = vector;
}

Light::Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec4 vector)
{
    ambient_ = ambient;
    diffuse_ = diffuse;
    specular_ = specular;

    vector_ = vector;
}

Light::~Light()
{
}
