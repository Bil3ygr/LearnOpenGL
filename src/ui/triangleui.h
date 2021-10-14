#pragma once

#ifndef SRC_UI_TRIANGLEUI_H_
#define SRC_UI_TRIANGLEUI_H_

#include "baseui.h"

class TriangleUI : public BaseUI
{
public:
    ~TriangleUI() {}

    void Render() override final;
};

#endif // !SRC_UI_TRIANGLEUI_H_
