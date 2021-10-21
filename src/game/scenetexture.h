#pragma once

#ifndef SRC_GAME_SCENETEXTURE_H_
#define SRC_GAME_SCENETEXTURE_H_

#include "scenewithui.h"

class SceneTexture : public SceneWithUI
{
public:
    ~SceneTexture() {}

    void RenderUI();

    void Enter();
};

#endif // !SRC_GAME_SCENETEXTURE_H_
