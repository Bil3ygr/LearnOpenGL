#pragma once

#ifndef SRC_SCENE_SCENECOLOR_H_
#define SRC_SCENE_SCENECOLOR_H_

#include <memory>

#include "scene.h"
#include "utils/public/lightmanager.h"
#include "ui/public/colorui.h"

class SceneColor : public Scene
{
public:
    SceneColor();
    ~SceneColor() override;

    const SceneType GetSceneType() noexcept override { return type_; }

    void Enter() override;
    void Leave() override;

private:
    const SceneType type_ = SceneType::kColor;
    std::shared_ptr<Light> light_;

    glm::vec3 light_translation_;

    ColorUI* ui_;
};

#endif // !SRC_SCENE_SCENECOLOR_H_
