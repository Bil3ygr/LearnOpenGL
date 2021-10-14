#pragma once

#ifndef SRC_DRAWER_LIGHTCASTERDRAWER_H_
#define SRC_DRAWER_LIGHTCASTERDRAWER_H_

#include "basedrawer.h"

#include "camera/cameramanager.h"
#include "utils/lightmanager.h"

class LightcasterDrawer : public BaseDrawer
{
public:
    LightcasterDrawer();
    ~LightcasterDrawer() override;

    void Init();

    void SetLight(std::shared_ptr<DirLight> light) { light_ = light; }

protected:
    virtual void _Render() override;

    SCamera camera_;
    std::shared_ptr<DirLight> light_;
    GLuint texture_;
    GLuint specular_texture_;
};

class LightcasterPointLightDrawer : public LightcasterDrawer
{
public:
    void Init();

    void SetLight(std::shared_ptr<PointLight> light) { light_ = light; }

protected:
    void _Render() override;

    std::shared_ptr<PointLight> light_;
};

class LightcasterSpotLightDrawer : public LightcasterDrawer
{
public:
    void Init();

    void SetLight(std::shared_ptr<SpotLight> light) { light_ = light; }

protected:
    void _Render() override;

    std::shared_ptr<SpotLight> light_;

    GLuint spot_texture_;
};

#endif // !SRC_DRAWER_LIGHTCASTERDRAWER_H_
