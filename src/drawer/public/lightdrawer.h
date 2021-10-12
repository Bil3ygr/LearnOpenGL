#pragma once

#ifndef SRC_DRAWER_LIGHTDRAWER_H_
#define SRC_DRAWER_LIGHTDRAWER_H_

#include "basedrawer.h"

#include "camera/public/cameramanager.h"
#include "utils/public/lightmanager.h"

class LightDrawer : public BaseDrawer
{
public:
    LightDrawer();
    virtual ~LightDrawer() override;

    void Init();

    void SetLight(std::shared_ptr<Light> light) { light_ = light; }

protected:
    virtual void _Render();

    SCamera camera_;
    std::shared_ptr<Light> light_;
};

#endif // !SRC_DRAWER_LIGHTDRAWER_H_
