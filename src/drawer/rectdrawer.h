#pragma once

#ifndef SRC_DRAWER_RECTDRAWER_H_
#define SRC_DRAWER_RECTDRAWER_H_

#include "basedrawer.h"

class RectDrawer : public BaseDrawer
{
public:
    void Init();

    void isLine(const bool& is_line) { is_line_ = is_line; }

protected:
    void _Render() override final;

    bool is_line_ = false;
};

#endif // !SRC_DRAWER_RECTDRAWER_H_
