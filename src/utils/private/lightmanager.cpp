#include "utils/public/lightmanager.h"

Light::Light()
{
    ambient_ = glm::vec3(1.0f);
    diffuse_ = glm::vec3(1.0f);
    specular_ = glm::vec3(1.0f);

    position_ = glm::vec3();
}

Light::Light(glm::vec3 position)
{
    ambient_ = glm::vec3(1.0f);
    diffuse_ = glm::vec3(1.0f);
    specular_ = glm::vec3(1.0f);

    position_ = position;
}

Light::Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
    ambient_ = ambient;
    diffuse_ = diffuse;
    specular_ = specular;

    position_ = glm::vec3();
}

Light::Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 position)
{
    ambient_ = ambient;
    diffuse_ = diffuse;
    specular_ = specular;

    position_ = position;
}

Light::~Light()
{
}
