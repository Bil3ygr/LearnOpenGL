#pragma once

#ifndef SRC_UTILS_KEYBOARDMANAGER_H_
#define SRC_UTILS_KEYBOARDMANAGER_H_

#include <functional>
#include <map>
#include <vector>
#include <string>

#include "GLFW/glfw3.h"

#include "singleton.h"

typedef std::map<std::string, std::function<void()> > Functions;

class KeyboardManager : public Singleton<KeyboardManager>
{
    friend class Singleton<KeyboardManager>;
private:
    KeyboardManager();
    ~KeyboardManager();

public:
    void RegisterKeyPressCallback(const GLuint& key, const std::string& id, std::function<void()>&& callback);
    void UnregisterKeyPressCallback(const GLuint& key, const std::string& id);
    void ProcessKeyEvent(GLFWwindow* window);

private:
    void ProcessKeyEvent(GLFWwindow* window, GLenum event);

    std::map<GLuint, Functions> press_map_;
};

#define REGISTER_KEYBOARD_PRESS(KEY, ID, CALLBACK) \
    KeyboardManager::Instance().RegisterKeyPressCallback(KEY, ID, []() -> void { \
        CALLBACK; \
    })

#endif // !SRC_UTILS_KEYBOARDMANAGER_H_
