#pragma once

#ifndef SRC_UI_COLORUI_H_
#define SRC_UI_COLORUI_H_

#include "baseui.h"

class ColorUI : public BaseUI
{
public:
    ~ColorUI() {}

    void Render() override;
};

#endif // !SRC_UI_COLORUI_H_
