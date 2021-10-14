#include "common/transform.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/quaternion.hpp"

Transform::Transform()
{
    translate_ = glm::vec3();
    rotate_ = glm::vec3();
    scale_ = glm::vec3(1.0f);
}

Transform::Transform(const Transform& trans)
{
    translate_ = trans.translate();
    rotate_ = trans.rotate();
    scale_ = trans.scale();
}

glm::mat4 Transform::transform()
{
    glm::mat4 trans = glm::scale(glm::mat4(1.0f), scale_);
    trans = glm::toMat4(glm::quat(rotate_)) * trans;
    trans = glm::translate(trans, translate_);
    return trans;
}
