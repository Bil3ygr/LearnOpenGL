#pragma once

#ifndef SRC_LIGHT_SPOTLIGHT_H_
#define SRC_LIGHT_SPOTLIGHT_H_

#include "baselight.h"

class SpotLight : public BaseLight
{
public:
    SpotLight(glm::vec3 pos = glm::vec3(), glm::vec3 dir = glm::vec3()) : BaseLight(), position_(pos), direction_(dir)
    {
        cutoff_ = 0.0f;
        outter_cutoff_ = 0.0f;
    }
    SpotLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 pos = glm::vec3(), glm::vec3 dir = glm::vec3()) :
        BaseLight(ambient, diffuse, specular), position_(pos), direction_(dir)
    {
        cutoff_ = 0.0f;
        outter_cutoff_ = 0.0f;
    }
    ~SpotLight() {}

    void position(const glm::vec3& pos) { position_ = pos; }
    glm::vec3 position() const { return position_; }
    void direction(const glm::vec3& dir) { direction_ = dir; }
    glm::vec3 direction() const { return direction_; }

    void cutoff(const float& value) { cutoff_ = value; }
    float cutoff() const { return cutoff_; }
    void outterCutoff(const float& value) { outter_cutoff_ = value; }
    float outterCutoff() const { return outter_cutoff_; }

private:
    glm::vec3 position_;
    glm::vec3 direction_;
    float cutoff_;
    float outter_cutoff_;
};

#endif // !SRC_LIGHT_SPOTLIGHT_H_
