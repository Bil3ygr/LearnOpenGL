#pragma once

#ifndef SRC_GAME_SCENETRIANGLE_H_
#define SRC_GAME_SCENETRIANGLE_H_

#include "scenewithui.h"

#include "utils/singleton.h"

class SceneTriangle: public SceneWithUI
{
public:
    ~SceneTriangle() override;

    void Render();
    void RenderUI();

    void Enter() override;
    void Leave() override;
};

#endif // !SRC_GAME_SCENETRIANGLE_H_
