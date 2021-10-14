#include "camera/camerahelper.h"

EulerAngle::~EulerAngle()
{
}

glm::vec3 EulerAngle::ToVec3()
{
    const float _yaw = yaw();
    const float _pitch = pitch();
    return glm::vec3(
        cos(glm::radians(_yaw)) * cos(glm::radians(_pitch)),
        sin(glm::radians(_pitch)),
        sin(glm::radians(_yaw)) * cos(glm::radians(_pitch))
    );
}
