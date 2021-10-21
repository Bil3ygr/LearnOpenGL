# pragma once

#ifndef SRC_SCENE_SCENEMANAGER_H_
#define SRC_SCENE_SCENEMANAGER_H_

#include <functional>
#include <map>

#include "scene.h"
#include "utils/singleton.h"
#include "ui/uimanager.h"

class SceneManager : public Singleton<SceneManager>
{
    friend class Singleton<SceneManager>;
private:
    SceneManager();
    ~SceneManager();

public:
    // void RegisterSceneType(const SceneType& type, std::function<Scene*()>&& function);
    // Scene* CreateScene(const SceneType& type);

    // void SwitchScene(const SceneType& type);
    void SwitchScene(Scene* scene);
    void RenderScene();
    Scene* GetCurrentScene() const noexcept  { return current_scene_; }

private:
    Scene* current_scene_;
    // std::map<SceneType, std::function<Scene*()> > factory_;
};


#define REGISTER_SCENE_CREATOR(SCENE_TYPE, SCENE_CLASS) \
    SceneManager::Instance().RegisterSceneType(SCENE_TYPE, []() -> Scene* { \
        return new SCENE_CLASS(); \
    })

#define SWITCH_SCENE(SCENE_TYPE) \
    SceneManager::Instance().SwitchScene(SCENE_TYPE)
#endif  // SRC_SCENE_SCENEMANAGER_H_
