#pragma once

#ifndef SRC_UTILS_MOUSEMANAGER_H_
#define SRC_UTILS_MOUSEMANAGER_H_

#include <functional>
#include <map>
#include <string>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "utils/singleton.h"
#include "mainwindow.h"

enum class EventType
{
    kMouseMove,
    kMouseClick,
    kMouseDoubleClick,
};

typedef std::function<void(float, float)> MouseCallback;
typedef std::function<void(int, int, int)> ButtonCallback;

class MouseManager : public Singleton<MouseManager>
{
    friend class Singleton<MouseManager>;
private:
    MouseManager();
    ~MouseManager();

public:
    void moveEnable(const bool& enable) { move_enable_ = enable; }
    const bool& moveEnable() const { return move_enable_; }
    void scrollEnable(const bool& enable) { scroll_enable_ = enable; }
    const bool& scrollEnable() const { return scroll_enable_; }
    void buttonEnable(const bool& enable) { button_enable_ = enable; }
    const bool& buttonEnable() const { return button_enable_; }

    void RegisterMouseMoveCallback(const std::string& id, MouseCallback&& callback);
    void UnregisterMouseMoveCallback(const std::string& id);
    void ProcessMouseMoveEvent(GLFWwindow* window, float x, float y);

    void RegisterMouseScrollCallback(const std::string& id, MouseCallback&& callback);
    void UnregisterMouseScrollCallback(const std::string& id);
    void ProcessMouseScrollEvent(GLFWwindow* window, float x, float y);

    void RegisterMouseButtonCallback(const std::string& id, ButtonCallback&& callback);
    void UnregisterMouseButtonCallback(const std::string& id);
    void ProcessMouseButtonEvent(GLFWwindow* window, int button, int action, int mods);

private:
    std::map<std::string, MouseCallback> move_callbacks_;
    std::map<std::string, MouseCallback> scroll_callbacks_;
    std::map<std::string, ButtonCallback> button_callbacks_;
    bool move_enable_;
    bool scroll_enable_;
    bool button_enable_;
};

#define REGISTER_MOUSE_MOVE(ID, CALLBACK) \
    MouseManager::Instance().RegisterMouseMoveCallback(ID, [this](float x, float y) -> void { \
        CALLBACK(x, y); \
    })
#define REGISTER_MOUSE_SCROLL(ID, CALLBACK) \
    MouseManager::Instance().RegisterMouseScrollCallback(ID, [this](float x, float y) -> void { \
        CALLBACK(x, y); \
    })
#define REGISTER_MOUSE_BUTTON(ID, CALLBACK) \
    MouseManager::Instance().RegisterMouseButtonCallback(ID, [](int button, int action, int mods) -> void { \
        CALLBACK(button, action, mods); \
    })

#endif // !SRC_UTILS_MOUSEMANAGER_H_
