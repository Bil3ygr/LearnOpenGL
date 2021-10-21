#pragma once

#ifndef SRC_GAME_SCENEWITHUI_H_
#define SRC_GAME_SCENEWITHUI_H_

#include "scene/scene.h"

class SceneWithUI : public Scene
{
public:
    virtual void RenderUI() {}
};

#endif // !SRC_GAME_SCENEWITHUI_H_
