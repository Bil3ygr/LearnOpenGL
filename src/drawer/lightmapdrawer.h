#pragma once

#ifndef SRC_DRAWER_LIGHTMAPDRAWER_H_
#define SRC_DRAWER_LIGHTMAPDRAWER_H_

#include <vector>

#include "basedrawer.h"
#include "camera/cameramanager.h"
#include "utils/lightmanager.h"

class LightmapDrawer : public BaseDrawer
{
public:
    LightmapDrawer();
    virtual ~LightmapDrawer() override;

    void Init();

    void SetLight(std::shared_ptr<PointLight> light) { light_ = light; }

protected:
    virtual void _Render();

    SCamera camera_;
    std::shared_ptr<PointLight> light_;
    GLuint texture_;
    GLuint specular_texture_;
};

#endif // !SRC_DRAWER_LIGHTMAPDRAWER_H_
