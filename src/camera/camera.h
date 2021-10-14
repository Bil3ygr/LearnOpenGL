#pragma once

#ifndef SRC_CAMERA_CAMERA_H_
#define SRC_CAMERA_CAMERA_H_

#include "glm/gtc/matrix_transform.hpp"

#include "camerahelper.h"
#include "utils/shadermanager.h"
#include "utils/timemanager.h"

class Camera
{
public:
    Camera();
    Camera(glm::vec3 pos, glm::vec3 front, glm::vec3 up);
    ~Camera();

    void Register();

    void Update();
    void Update(glm::mat4 view);

    void LookAt(glm::vec3 pos, glm::vec3 front, glm::vec3 up);
    const glm::mat4& LookAt();
    void UpdateFront(float x, float y);
    void UpdateFov(float x, float y);
    void SetMoveSpeed(float speed);
    void SetProgram(const GLuint& program) { program_ = program; }

    void enable(const bool& enable) { enable_ = enable; }
    const bool& enable() const { return enable_; }
    const float& speed() const { return speed_ * TimeManager::Instance().deltaTime(); }
    void pos(const glm::vec3& pos) { pos_ = pos; }
    const glm::vec3& pos() const { return pos_; }
    const float& fov() const { return fov_; }
    const glm::vec3& front() const { return front_; }

    void MoveLeft();
    void MoveRight();
    void MoveFront();
    void MoveBack();

    void ResetMousePos();

private:
    bool enable_;
    float speed_;
    glm::vec3 pos_;
    glm::vec3 front_;
    glm::vec3 up_;
    GLuint program_;

    EulerAngle* euler_angle_;
    glm::vec2 mouse_pos_;
    bool first_mouse_;
    float fov_;
};

#define VEC3_TO_4(x, y, z, i) glm::vec4(x[i], y[i], z[i], 0.0f)

#endif // !SRC_CAMERA_CAMERA_H_
