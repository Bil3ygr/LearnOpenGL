#pragma once

#ifndef SRC_LIGHT_POINTLIGHT_H_
#define SRC_LIGHT_POINTLIGHT_H_

#include "baselight.h"

class PointLight : public BaseLight
{
public:
    PointLight(glm::vec3 pos = glm::vec3()) : BaseLight(), position_(pos)
    {
        constant_ = 1.0f;
        linear_ = 0.0f;
        quadratic_ = 0.0f;
    }
    PointLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 pos = glm::vec3()) :
        BaseLight(ambient, diffuse, specular), position_(pos)
    {
        constant_ = 1.0f;
        linear_ = 0.0f;
        quadratic_ = 0.0f;
    }
    ~PointLight() {}

    void position(const glm::vec3& pos) { position_ = pos; }
    const glm::vec3 position() const { return position_; }

    void constant(const float& value) { constant_ = value; }
    const float constant() const { return constant_; }
    void linear(const float& value) { linear_ = value; }
    const float linear() const { return linear_; }
    void quadratic(const float& value) { quadratic_ = value; }
    const float quadratic() const { return quadratic_; }

private:
    glm::vec3 position_;

    float constant_;
    float linear_;
    float quadratic_;
};

#endif // !SRC_LIGHT_POINTLIGHT_H_
