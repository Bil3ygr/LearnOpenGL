#pragma once

#ifndef SRC_GAME_SCENETRIANGLE_H_
#define SRC_GAME_SCENETRIANGLE_H_

#include "scenewithui.h"

class SceneTriangle: public SceneWithUI
{
public:
    ~SceneTriangle() {}

    void RenderUI() override;

    void Enter() override;
};

#endif // !SRC_GAME_SCENETRIANGLE_H_
