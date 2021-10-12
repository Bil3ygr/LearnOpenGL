#pragma once

#ifndef SRC_UTILS_LIGHTMANAGER_H_
#define SRC_UTILS_LIGHTMANAGER_H_

#include "glm/glm.hpp"

class Light
{
public:
    Light();
    Light(glm::vec4 vector);
    Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec4 vector = glm::vec4(glm::vec3(), 1.0f));
    ~Light();

    void ambient(const glm::vec3& value) { ambient_ = value; }
    const glm::vec3 ambient() const { return ambient_; }
    void diffuse(const glm::vec3& value) { diffuse_ = value; }
    const glm::vec3 diffuse() const { return diffuse_; }
    void specular(const glm::vec3& value) { specular_ = value; }
    const glm::vec3 specular() const { return specular_; }
    void vector(const glm::vec4& value) { vector_ = value; }
    const glm::vec4 vector() const { return vector_; }

private:
    glm::vec3 ambient_;
    glm::vec3 diffuse_;
    glm::vec3 specular_;

    glm::vec4 vector_;
};

class SpotLight : public Light
{
public:
    SpotLight() : Light(), light_dir_(glm::vec3()), cutoff_(0), outter_cutoff_(0) {}
    SpotLight(glm::vec3 light_dir, float cutoff, float outter_cutoff) :
        Light(), light_dir_(light_dir), cutoff_(cutoff), outter_cutoff_(outter_cutoff) {}
    ~SpotLight() {}

    void lightDir(const glm::vec3& dir) { light_dir_ = dir; }
    glm::vec3 lightDir() const { return light_dir_; }
    void cutoff(const float& value) { cutoff_ = value; }
    float cutoff() const { return cutoff_; }
    void outtercutoff(const float& value) { outter_cutoff_ = value; }
    float outtercutoff() const { return outter_cutoff_; }

private:
    glm::vec3 light_dir_;
    float cutoff_;
    float outter_cutoff_;
};

#endif // !SRC_UTILS_LIGHTMANAGER_H_
