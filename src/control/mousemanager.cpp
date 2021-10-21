#include "mousemanager.h"

#include "utils/helper.h"

void MouseMoveCallback(GLFWwindow* window, double x, double y)
{
    MouseManager::Instance().ProcessMouseMoveEvent(window, x, y);
}

void MouseScrollCallback(GLFWwindow* window, double x, double y)
{
    MouseManager::Instance().ProcessMouseScrollEvent(window, x, y);
}

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    MouseManager::Instance().ProcessMouseButtonEvent(window, button, action, mods);
}

MouseManager::MouseManager()
{
    move_callbacks_ = std::map<std::string, MouseCallback>();
    scroll_callbacks_ = std::map<std::string, MouseCallback>();
    button_callbacks_ = std::map<std::string, ButtonCallback>();
    move_enable_ = false;
    scroll_enable_ = false;
    button_enable_ = false;

    glfwSetCursorPosCallback(const_cast<GLFWwindow*>(MainWindow::Instance().window()), MouseMoveCallback);
    glfwSetScrollCallback(const_cast<GLFWwindow*>(MainWindow::Instance().window()), MouseScrollCallback);
    glfwSetMouseButtonCallback(const_cast<GLFWwindow*>(MainWindow::Instance().window()), MouseButtonCallback);
}

MouseManager::~MouseManager()
{
    move_callbacks_.clear();
    scroll_callbacks_.clear();
}

void MouseManager::RegisterMouseMoveCallback(const std::string& id, MouseCallback&& callback)
{
    auto iter = move_callbacks_.find(id);
    if (iter == move_callbacks_.end())
        move_callbacks_[id] = callback;
    else
        WARNING("Mouse move event [%s] already exists\n", id.c_str());
}

void MouseManager::UnregisterMouseMoveCallback(const std::string& id)
{
    auto iter = move_callbacks_.find(id);
    if (iter == move_callbacks_.end())
        WARNING("Mouse move event [%s] not exists\n", id.c_str());
    else
        move_callbacks_.erase(iter);
}

void MouseManager::ProcessMouseMoveEvent(GLFWwindow* window, float x, float y)
{
    if (!move_enable_)
        return;

    for (auto iter = move_callbacks_.begin(); iter != move_callbacks_.end(); ++iter)
        iter->second(x, y);
}

void MouseManager::RegisterMouseScrollCallback(const std::string& id, MouseCallback&& callback)
{
    auto iter = scroll_callbacks_.find(id);
    if (iter == scroll_callbacks_.end())
        scroll_callbacks_[id] = callback;
    else
        WARNING("Mouse scroll event [%s] already exists\n", id.c_str());
}

void MouseManager::UnregisterMouseScrollCallback(const std::string& id)
{
    auto iter = scroll_callbacks_.find(id);
    if (iter == scroll_callbacks_.end())
        WARNING("Mouse scroll event [%s] not exists\n", id.c_str());
    else
        scroll_callbacks_.erase(iter);
}

void MouseManager::ProcessMouseScrollEvent(GLFWwindow* window, float x, float y)
{
    if (!scroll_enable_)
        return;

    for (auto iter = scroll_callbacks_.begin(); iter != scroll_callbacks_.end(); ++iter)
        iter->second(x, y);
}

void MouseManager::RegisterMouseButtonCallback(const std::string& id, ButtonCallback&& callback)
{
    auto iter = button_callbacks_.find(id);
    if (iter == button_callbacks_.end())
        button_callbacks_[id] = callback;
    else
        WARNING("Mouse scroll event [%s] already exists\n", id.c_str());
}

void MouseManager::UnregisterMouseButtonCallback(const std::string& id)
{
    auto iter = button_callbacks_.find(id);
    if (iter == button_callbacks_.end())
        WARNING("Mouse scroll event [%s] not exists\n", id.c_str());
    else
        button_callbacks_.erase(iter);
}

void MouseManager::ProcessMouseButtonEvent(GLFWwindow* window, int button, int action, int mods)
{
    if (!button_enable_)
        return;

    for (auto iter = button_callbacks_.begin(); iter != button_callbacks_.end(); ++iter)
        iter->second(button, action, mods);
}
