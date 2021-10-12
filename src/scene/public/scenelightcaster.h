#pragma once

#ifndef SRC_SCENE_SCENELIGHTCASTER_H_
#define SRC_SCENE_SCENELIGHTCASTER_H_

#include <memory>

#include "scene.h"
#include "utils/public/lightmanager.h"
#include "ui/public/lightcasterui.h"

class SceneLightcaster : public Scene
{
public:
    SceneLightcaster();
    ~SceneLightcaster() override;

    const SceneType GetSceneType() noexcept override { return type_; }

    void Enter() override;
    void Leave() override;

    void SetLightAmbient(const glm::vec3& value);
    glm::vec3 GetLightAmbient();
    void SetLightDiffuse(const glm::vec3& value);
    glm::vec3 GetLightDiffuse();
    void SetLightSpecular(const glm::vec3& value);
    glm::vec3 GetLightSpecular();

    void SetLightVector3(const glm::vec3& value);
    glm::vec3 GetLightVector3();

    void SetIsPointLight(const bool& check);
    bool IsPointLight();

    void SetSpotLightCutoff(const float& cutoff);
    float GetSpotLightCutoff();
    void SetSpotLightOutterCutoff(const float& outter_cutoff);
    float GetSpotLightOutterCutoff();

private:
    const SceneType type_ = SceneType::kLightcaster;
    std::shared_ptr<Light> light_;
    std::shared_ptr<SpotLight> spot_light_;
    LightcasterUI* ui_;
};

#endif // !SRC_SCENE_SCENELIGHTCASTER_H_
