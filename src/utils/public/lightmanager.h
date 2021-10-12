#pragma once

#ifndef SRC_UTILS_LIGHTMANAGER_H_
#define SRC_UTILS_LIGHTMANAGER_H_

#include "glm/glm.hpp"

class Light
{
public:
    Light();
    Light(glm::vec3 position);
    Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
    Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 position);
    ~Light();

    void ambient(const glm::vec3& value) { ambient_ = value; }
    const glm::vec3 ambient() const { return ambient_; }
    void diffuse(const glm::vec3& value) { diffuse_ = value; }
    const glm::vec3 diffuse() const { return diffuse_; }
    void specular(const glm::vec3& value) { specular_ = value; }
    const glm::vec3 specular() const { return specular_; }
    void position(const glm::vec3& value) { position_ = value; }
    const glm::vec3 position() const { return position_; }

private:
    glm::vec3 ambient_;
    glm::vec3 diffuse_;
    glm::vec3 specular_;

    glm::vec3 position_;
};

#endif // !SRC_UTILS_LIGHTMANAGER_H_
