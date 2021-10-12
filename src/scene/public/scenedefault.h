#pragma once

#ifndef SRC_SCENE_SCENEDEFAULT_H_
#define SRC_SCENE_SCENEDEFAULT_H_

#include <vector>

#include "scene.h"

#include "ui/public/defaultui.h"

class SceneDefault : public Scene
{
public:
    ~SceneDefault() override;

    const SceneType GetSceneType() noexcept override { return type_; }

    void Enter() override;
    void Leave() override;

private:
    const SceneType type_ = SceneType::kDefault;
    DefaultUI* ui_;
};

#endif // !SRC_SCENE_SCENEDEFAULT_H_
