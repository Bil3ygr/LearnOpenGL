#pragma once

#ifndef SRC_LIGHT_DIRLIGHT_H_
#define SRC_LIGHT_DIRLIGHT_H_

#include "baselight.h"

class DirLight : public BaseLight
{
public:
    DirLight(glm::vec3 dir = glm::vec3()) : BaseLight(), direction_(dir) {}
    DirLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 dir = glm::vec3()) :
        BaseLight(ambient, diffuse, specular), direction_(dir) {}
    ~DirLight() {}

    void direction(const glm::vec3& value) { direction_ = value; }
    const glm::vec3 direction() const { return direction_; }

private:
    glm::vec3 direction_;
};

#endif // !SRC_LIGHT_DIRLIGHT_H_
