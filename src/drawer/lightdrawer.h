#pragma once

#ifndef SRC_DRAWER_LIGHTDRAWER_H_
#define SRC_DRAWER_LIGHTDRAWER_H_

#include "basedrawer.h"

#include "camera/cameramanager.h"
#include "light/pointlight.h"
#include "light/spotlight.h"

class LightDrawer : public BaseDrawer
{
public:
    LightDrawer();
    virtual ~LightDrawer() override;

    void Init();

    void SetPointLight(std::shared_ptr<PointLight> light);
    void SetSpotLight(std::shared_ptr<SpotLight> light);

protected:
    virtual void _Render();

    SCamera camera_;
    std::shared_ptr<PointLight> point_light_;
    std::shared_ptr<SpotLight> spot_light_;
};

#endif // !SRC_DRAWER_LIGHTDRAWER_H_
