#pragma once

#ifndef SRC_SCENE_SCENELIGHTMAP_H_
#define SRC_SCENE_SCENELIGHTMAP_H_

#include <memory>

#include "scenemanager.h"
#include "utils/public/lightmanager.h"

class SceneLightmap : public Scene
{
public:
    SceneLightmap();
    ~SceneLightmap() override;

    const SceneType GetSceneType() noexcept override { return type_; }

    void Enter() override;

private:
    const SceneType type_ = SceneType::kLightmap;
    std::shared_ptr<Light> light_;
};

#endif // SRC_SCENE_SCENELIGHTMAP_H_
