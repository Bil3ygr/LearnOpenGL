#pragma once

#ifndef SRC_LIGHT_BASELIGHT_H_
#define SRC_LIGHT_BASELIGHT_H_

#include "glm/glm.hpp"

class BaseLight
{
public:
    BaseLight() : ambient_(glm::vec3(1.0f)), diffuse_(glm::vec3(1.0f)), specular_(glm::vec3(1.0f)) {}
    BaseLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) :
        ambient_(ambient), diffuse_(diffuse), specular_(specular) {}
    ~BaseLight() {}

    void ambient(const glm::vec3& value) { ambient_ = value; }
    const glm::vec3 ambient() const { return ambient_; }
    void diffuse(const glm::vec3& value) { diffuse_ = value; }
    const glm::vec3 diffuse() const { return diffuse_; }
    void specular(const glm::vec3& value) { specular_ = value; }
    const glm::vec3 specular() const { return specular_; }

private:
    glm::vec3 ambient_;
    glm::vec3 diffuse_;
    glm::vec3 specular_;
};

#endif // !SRC_LIGHT_BASELIGHT_H_
