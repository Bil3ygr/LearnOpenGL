#pragma once

#ifndef SRC_SCENE_SCENESPACE_H_
#define SRC_SCENE_SCENESPACE_H_

#include "scenemanager.h"

#include "ui/public/spaceui.h"

class SceneSpace: public Scene
{
public:
    ~SceneSpace() override;

    const SceneType GetSceneType() noexcept override { return type_; }

    void Enter() override;
    void Leave() override;

private:
    const SceneType type_ = SceneType::kSpace;
    SpaceUI* ui_;
};

#endif // !SRC_SCENE_SCENESPACE_H_
