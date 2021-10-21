#pragma once

#ifndef SRC_SCENE_SCENELIGHTCASTER_H_
#define SRC_SCENE_SCENELIGHTCASTER_H_

#include <memory>

#include "scene.h"
#include "light/dirlight.h"
#include "light/pointlight.h"
#include "light/spotlight.h"
#include "ui/lightcasterui.h"

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

    void SetDirLightDirection(const glm::vec3& value);
    glm::vec3 GetDirLightDirection();

    void SetPointLightPosition(const glm::vec3& value);
    glm::vec3 GetPointLightPosition();
    void SetPointLightConstant(const float& value);
    float GetPointLightConstant();
    void SetPointLightLinear(const float& value);
    float GetPointLightLinear();
    void SetPointLightQuadratic(const float& value);
    float GetPointLightQuadratic();

    void SetSpotLightPosition(const glm::vec3& value);
    glm::vec3 GetSpotLightPosition();
    void SetSpotLightDirection(const glm::vec3& value);
    glm::vec3 GetSpotLightDirection();
    void SetSpotLightCutoff(const float& cutoff);
    float GetSpotLightCutoff();
    void SetSpotLightOutterCutoff(const float& outter_cutoff);
    float GetSpotLightOutterCutoff();

private:
    const SceneType type_ = SceneType::kLightcaster;
    std::shared_ptr<DirLight> dir_light_;
    std::shared_ptr<PointLight> point_light_;
    std::shared_ptr<SpotLight> spot_light_;
    LightcasterUI* ui_;
};

#endif // !SRC_SCENE_SCENELIGHTCASTER_H_
