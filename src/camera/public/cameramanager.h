#pragma once

#ifndef SRC_CAMERA_CAMERAMANAGER_H_
#define SRC_CAMERA_CAMERAMANAGER_H_

#include <map>
#include <memory>

#include "glm/gtc/matrix_transform.hpp"

#include "camera.h"
#include "utils/public/singleton.h"

typedef std::shared_ptr<Camera> SCamera;

class CameraManager : public Singleton<CameraManager>
{
    friend class Singleton<CameraManager>;
private:
    CameraManager();
    ~CameraManager();

public:
    SCamera GetDefaultCamera();
    SCamera GetCamera(const int& id);
    SCamera CreateCamera(const int& id);
    SCamera CreateCamera(const int& id, const glm::vec3& pos, const glm::vec3& front, const glm::vec3& up);
    void DestroyCamera(const int& id);

    void MoveFront();
    void MoveBack();
    void MoveLeft();
    void MoveRight();

    void ResetMousePos();

private:
    std::map<int, SCamera> cameras_;
};

#endif // !SRC_CAMERA_CAMERAMANAGER_H_
