#pragma once

#ifndef SRC_UI_DEFAULTUI_H_
#define SRC_UI_DEFAULTUI_H_

#include "baseui.h"

class DefaultUI : public BaseUI
{
public:
    ~DefaultUI() {}

    void Render() override final;
};

#endif // !SRC_UI_DEFAULTUI_H_
