#include "camera/cameramanager.h"

#include "GLFW/glfw3.h"

#include "utils/helper.h"
#include "utils/keyboardmanager.h"

CameraManager::CameraManager()
{
    cameras_ = std::map<int, SCamera>();
    // create default camera
    CreateCamera(0);

    REGISTER_KEYBOARD_PRESS(GLFW_KEY_W, "front", CameraManager::Instance().MoveFront());
    REGISTER_KEYBOARD_PRESS(GLFW_KEY_S, "back", CameraManager::Instance().MoveBack());
    REGISTER_KEYBOARD_PRESS(GLFW_KEY_A, "left", CameraManager::Instance().MoveLeft());
    REGISTER_KEYBOARD_PRESS(GLFW_KEY_D, "right", CameraManager::Instance().MoveRight());
}

CameraManager::~CameraManager()
{
    cameras_.clear();
}

SCamera CameraManager::GetDefaultCamera()
{
    return GetCamera(0);
}

SCamera CameraManager::GetCamera(const int& id)
{
    auto iter = cameras_.find(id);
    return iter != cameras_.end() ? iter->second : nullptr;
}

SCamera CameraManager::CreateCamera(const int& id)
{
    SCamera camera = GetCamera(id);
    if (camera)
    {
        WARNING("Camera with id [%s] already exists\n", TO_CHAR(id));
        return camera;
    }

    camera = std::make_shared<Camera>();
    cameras_[id] = camera;
    return camera;
}

SCamera CameraManager::CreateCamera(const int& id, const glm::vec3& pos, const glm::vec3& front, const glm::vec3& up)
{
    SCamera camera = GetCamera(id);
    if (camera)
    {
        WARNING("Camera with id [%s] already exists\n", TO_CHAR(id));
        return camera;
    }

    camera = std::make_shared<Camera>(pos, front, up);
    cameras_[id] = camera;
    return camera;
}

void CameraManager::DestroyCamera(const int& id)
{
    auto iter = cameras_.find(id);
    if (iter == cameras_.end())
        WARNING("Camera [%s] not found, destroy error\n", TO_CHAR(id));
    else
        cameras_.erase(iter);
}

void CameraManager::MoveFront()
{
    SCamera camera = GetDefaultCamera();
    if (!camera)
        return;
    camera.get()->MoveFront();
}

void CameraManager::MoveBack()
{
    SCamera camera = GetDefaultCamera();
    if (!camera)
        return;
    camera.get()->MoveBack();
}

void CameraManager::MoveLeft()
{
    SCamera camera = GetDefaultCamera();
    if (!camera)
        return;
    camera.get()->MoveLeft();
}

void CameraManager::MoveRight()
{
    SCamera camera = GetDefaultCamera();
    if (!camera)
        return;
    camera.get()->MoveRight();
}

void CameraManager::ResetMousePos()
{
    for (auto iter = cameras_.begin(); iter != cameras_.end(); ++iter)
        iter->second->ResetMousePos();
}
