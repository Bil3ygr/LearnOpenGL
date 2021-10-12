#pragma once

#ifndef SRC_UI_LIGHTMAPUI_H_
#define SRC_UI_LIGHTMAPUI_H_

#include "baseui.h"

class LightmapUI : public BaseUI
{
public:
    ~LightmapUI() {}

    void Render() override final;
};

#endif // !SRC_UI_LIGHTMAPUI_H_
