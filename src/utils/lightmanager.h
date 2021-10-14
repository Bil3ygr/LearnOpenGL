#pragma once

#ifndef SRC_UTILS_LIGHTMANAGER_H_
#define SRC_UTILS_LIGHTMANAGER_H_

#include "glm/glm.hpp"

class Light
{
public:
    Light() : ambient_(glm::vec3(1.0f)), diffuse_(glm::vec3(1.0f)), specular_(glm::vec3(1.0f)) {}
    Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) :
        ambient_(ambient), diffuse_(diffuse), specular_(specular) {}
    ~Light() {}

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

class DirLight : public Light
{
public:
    DirLight(glm::vec3 dir = glm::vec3()) : Light(), direction_(dir) {}
    DirLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 dir = glm::vec3()) :
        Light(ambient, diffuse, specular), direction_(dir) {}
    ~DirLight() {}

    void direction(const glm::vec3& value) { direction_ = value; }
    const glm::vec3 direction() const { return direction_; }

private:
    glm::vec3 direction_;
};

class PointLight : public Light
{
public:
    PointLight(glm::vec3 pos = glm::vec3()) : Light(), position_(pos)
    {
        constant_ = 1.0f;
        linear_ = 0.0f;
        quadratic_ = 0.0f;
    }
    PointLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 pos = glm::vec3()) :
        Light(ambient, diffuse, specular), position_(pos)
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

class SpotLight : public Light
{
public:
    SpotLight(glm::vec3 pos = glm::vec3(), glm::vec3 dir = glm::vec3()) : Light(), position_(pos), direction_(dir)
    {
        cutoff_ = 0.0f;
        outter_cutoff_ = 0.0f;
    }
    SpotLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 pos = glm::vec3(), glm::vec3 dir = glm::vec3()) :
        Light(ambient, diffuse, specular), position_(pos), direction_(dir)
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

#endif // !SRC_UTILS_LIGHTMANAGER_H_
