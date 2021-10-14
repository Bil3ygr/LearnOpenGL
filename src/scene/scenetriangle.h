#pragma once

#ifndef SRC_SCENE_SCENETRIANGLE_H_
#define SRC_SCENE_SCENETRIANGLE_H_

#include "scenemanager.h"

#include "ui/triangleui.h"

class SceneTriangle: public Scene
{
public:
    ~SceneTriangle() override;

    const SceneType GetSceneType() noexcept override { return type_; }

    void Enter() override;
    void Leave() override;

    void rectLine(const bool& is_line);
    const bool rectLine() const { return rect_line_; }

private:
    const SceneType type_ = SceneType::kTriangle;
    bool rect_line_ = false;
    TriangleUI* ui_;
};

#endif // !SRC_SCENE_SCENETRIANGLE_H_
