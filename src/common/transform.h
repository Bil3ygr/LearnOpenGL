#pragma once

#ifndef SRC_COMMON_TRANSFORM_H_
#define SRC_COMMON_TRANSFORM_H_

#include "glm/glm.hpp"

class Transform
{
public:
    Transform();
    Transform(const Transform& trans);
    ~Transform() {}

    void translate(const float& x, const float& y, const float& z) { translate(glm::vec3(x, y, z)); }
    void translate(const glm::vec3& value) { translate_ = value; }
    glm::vec3 translate() const { return translate_; }
    float x() { return translate_.x; }
    float y() { return translate_.y; }
    float z() { return translate_.z; }

    void rotate(const float& pitch, const float& yaw, const float& roll) { rotate(glm::vec3(pitch, yaw, roll)); }
    void rotate(const glm::vec3& value) { rotate_ = value; }
    glm::vec3 rotate() const { return rotate_; }
    float pitch() { return rotate_.x; }
    float yaw() { return rotate_.y; }
    float roll() { return rotate_.z; }

    void scale(const float& x, const float& y, const float& z) { scale(glm::vec3(x, y, z)); }
    void scale(const glm::vec3& value) { scale_ = value; }
    glm::vec3 scale() const { return scale_; }

    glm::mat4 transform();

private:
    glm::vec3 translate_;
    glm::vec3 rotate_;
    glm::vec3 scale_;
};

#endif // !SRC_COMMON_TRANSFORM_H_
