#include "utils/public/keyboardmanager.h"

#include <string>

#include "utils/public/helper.h"

KeyboardManager::KeyboardManager()
{
    press_map_ = std::map<GLuint, Functions>();
}

KeyboardManager::~KeyboardManager()
{
}

void KeyboardManager::RegisterKeyPressCallback(const GLuint& key, const std::string& id, std::function<void()>&& callback)
{
    auto iter = press_map_.find(key);
    if (iter == press_map_.end())
        press_map_[key] = Functions();
    Functions& callbacks = press_map_[key];
    auto iter_func = callbacks.find(id);
    if (iter_func == callbacks.end())
        callbacks[id] = callback;
    else
        WARNING("Key [%s] already has callback with id [%s]", TO_CHAR(key), id.c_str());
}

void KeyboardManager::UnregisterKeyPressCallback(const GLuint& key, const std::string& id)
{
    auto iter = press_map_.find(key);
    if (iter != press_map_.end())
    {
        Functions &callbacks = press_map_[key];
        auto iter_func = callbacks.find(id);
        if (iter_func != callbacks.end())
            callbacks.erase(iter_func);

        if (callbacks.empty())
            press_map_.erase(iter);
    }
}

void KeyboardManager::ProcessKeyEvent(GLFWwindow* window)
{
    ProcessKeyEvent(window, GLFW_PRESS);

    // else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    // {
    //     Scene *scene = SceneManager::Instance().GetCurrentScene();
    //     if (scene && scene->GetSceneType() == SceneType::kTexture)
    //         static_cast<SceneTexture *>(scene)->ChangeMixValue(0.01f);
    // }
    // else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    // {
    //     Scene *scene = SceneManager::Instance().GetCurrentScene();
    //     if (scene && scene->GetSceneType() == SceneType::kTexture)
    //         static_cast<SceneTexture *>(scene)->ChangeMixValue(-0.01f);
    // }
}

void KeyboardManager::ProcessKeyEvent(GLFWwindow* window, GLenum event)
{
    for (auto iter = press_map_.begin(); iter != press_map_.end(); ++iter)
    {
        if (glfwGetKey(window, iter->first) == event)
        {
            for (auto iter_func = iter->second.begin(); iter_func != iter->second.end(); ++iter_func)
                iter_func->second();
        }
    }
}
