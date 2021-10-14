#pragma once

#ifndef SRC_SCENE_SCENELIGHTMAP_H_
#define SRC_SCENE_SCENELIGHTMAP_H_

#include <memory>

#include "scenemanager.h"
#include "utils/public/lightmanager.h"
#include "ui/public/lightmapui.h"

class SceneLightmap : public Scene
{
public:
    SceneLightmap();
    ~SceneLightmap() override;

    const SceneType GetSceneType() noexcept override { return type_; }

    void Enter() override;
    void Leave() override;

    void SetLightAmbient(const glm::vec3& value);
    glm::vec3 GetLightAmbient();
    void SetLightDiffuse(const glm::vec3& value);
    glm::vec3 GetLightDiffuse();
    void SetLightSpecular(const glm::vec3& value);
    glm::vec3 GetLightSpecular();

private:
    const SceneType type_ = SceneType::kLightmap;
    std::shared_ptr<PointLight> light_;
    LightmapUI* ui_;
};

#endif // SRC_SCENE_SCENELIGHTMAP_H_
