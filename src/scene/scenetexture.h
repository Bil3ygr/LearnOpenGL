#pragma once

#ifndef SRC_SCENE_SCENETEXTURE_H_
#define SRC_SCENE_SCENETEXTURE_H_

#include "scenemanager.h"

// class SceneTexture: public Scene
// {
// public:
//     ~SceneTexture() override;

//     const SceneType GetSceneType() noexcept override { return type_; }

//     void Enter() override;
//     void Leave() override;

//     void mixValue(const float& mix_value);
//     const float mixValue() const { return mix_value_; }

//     void autoRotate(const bool& auto_rotate);
//     const bool autoRotate() const { return auto_rotate_; }
//     void rotateSpeed(const float& rotate_speed);
//     const float rotateSpeed() const { return rotate_speed_; }
//     void rotateRadian(const float& rotate_radian);
//     const float rotateRadian() const { return rotate_radian_; }
//     void scale(const glm::vec3& _scale);
//     const glm::vec3 scale() const { return scale_; }

// private:
//     const SceneType type_ = SceneType::kTexture;
//     float mix_value_ = 0.2f;

//     bool auto_rotate_ = true;
//     float rotate_speed_ = 1.0f;
//     float rotate_radian_ = 0.0f;
//     glm::vec3 scale_ = glm::vec3(1.0f);

//     TextureUI* ui_;
// };

#endif // !SRC_SCENE_SCENETEXTURE_H_
