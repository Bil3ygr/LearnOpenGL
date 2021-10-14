#include "scene/scenemanager.h"

#include <string>
#include <iostream>

#include "utils/helper.h"

SceneManager::SceneManager()
{
    factory_ = std::map<SceneType, std::function<Scene*()> >();
    current_scene_ = nullptr;
}

SceneManager::~SceneManager()
{
}

void SceneManager::RegisterSceneType(const SceneType& type, std::function<Scene*()>&& function)
{
    auto iter = factory_.find(type);
    if (iter != factory_.end())
    {
        WARNING("SceneType %s already exists\n", SceneTypeToString(type));
        return;
    }
    factory_[type] = function;

    INFO("Register scene type %s success\n", SceneTypeToString(type));
}

Scene* SceneManager::CreateScene(const SceneType& type)
{
    auto iter = factory_.find(type);
    if (iter == factory_.end())
    {
        WARNING("Cannot find creator of type %s\n", SceneTypeToString(type));
        return nullptr;
    }
    INFO("Create scene type %s success\n", SceneTypeToString(type));
    return iter->second();
}

void SceneManager::SwitchScene(const SceneType& type)
{
    if (current_scene_)
    {
        if (current_scene_->GetSceneType() == type)
            return;
        current_scene_->Leave();
    }

    current_scene_ = CreateScene(type);
    if (!current_scene_)
        return;

    current_scene_->Enter();
}


void SceneManager::RenderScene()
{
    if (current_scene_)
        current_scene_->Render();
}
