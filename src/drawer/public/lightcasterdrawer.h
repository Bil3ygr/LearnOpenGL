#pragma once

#ifndef SRC_DRAWER_LIGHTCASTERDRAWER_H_
#define SRC_DRAWER_LIGHTCASTERDRAWER_H_

#include "basedrawer.h"

#include "camera/public/cameramanager.h"
#include "utils/public/lightmanager.h"

class LightcasterDrawer : public BaseDrawer
{
public:
    LightcasterDrawer();
    ~LightcasterDrawer() override;

    void Init();

    void SetLight(std::shared_ptr<Light> light) { light_ = light; }

protected:
    virtual void _Render() override;

    SCamera camera_;
    std::shared_ptr<Light> light_;
    GLuint texture_;
    GLuint specular_texture_;
};

class LightcasterPointLightDrawer : public LightcasterDrawer
{
public:
    void Init();

protected:
    void _Render() override;
};

class LightcasterSpotLightDrawer : public LightcasterDrawer
{
public:
    void Init();

    void SetLight(std::shared_ptr<SpotLight> light) { light_ = light; }

protected:
    void _Render() override;

    std::shared_ptr<SpotLight> light_;
};

#endif // !SRC_DRAWER_LIGHTCASTERDRAWER_H_
