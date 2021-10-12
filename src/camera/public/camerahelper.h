#pragma once

#ifndef SRC_CAMERA_CAMERAHELPER_H_
#define SRC_CAMERA_CAMERAHELPER_H_

#include "glm/glm.hpp"

class EulerAngle
{
public:
    EulerAngle() { pitch_ = 0; yaw_ = -90.0f; roll_ = 0; }
    EulerAngle(float p, float y, float r) : pitch_(p), yaw_(y), roll_(r) {}
    virtual ~EulerAngle();

    void pitch(const float& p)
    {
        pitch_ = p;
        if (pitch_ > 89.0f)
            pitch_ = 89.0f;
        else if (pitch_ < -89.0f)
            pitch_ = -89.0f;
    }
    const float& pitch() const { return pitch_; }

    void yaw(const float& y)
    {
        yaw_ = y;
        if (yaw_ > 360.0f)
            yaw_ -= 360.0f;
        else if (yaw_ < 0.0f)
            yaw_ += 360.0f;
    }
    const float& yaw() const { return yaw_; }

    void roll(const float& r)
    {
        roll_ = r;
        if (roll_ > 360.0f)
            roll_ -= 360.0f;
        else if (roll_ < 0.0f)
            roll_ += 360.0f;
    }
    const float& roll() const { return roll_; }

    glm::vec3 ToVec3();

private:
    float pitch_;
    float yaw_;
    float roll_;
};

#define ADD_PITCH(angle, p) angle->pitch(angle->pitch() + p)
#define ADD_YAW(angle, y) angle->yaw(angle->yaw() + y)
#define ADD_ROLL(angle, r) angle->roll(angle->roll() + r)

#endif // !SRC_CAMERA_CAMERAHELPER_H_
