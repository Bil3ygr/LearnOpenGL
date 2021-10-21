#pragma once

#ifndef SRC_DRAWER_COLORDRAWER_H_
#define SRC_DRAWER_COLORDRAWER_H_

#include <vector>

#include "basedrawer.h"
#include "camera/cameramanager.h"
#include "light/pointlight.h"

class ColorDrawer : public BaseDrawer
{
public:
    ColorDrawer();
    virtual ~ColorDrawer() override;

    void Init();

    void SetLight(std::shared_ptr<PointLight> light) { light_ = light; }

protected:
    virtual void _Render();

    SCamera camera_;
    std::shared_ptr<PointLight> light_;
};

class ColorLightingDrawer : public ColorDrawer
{
public:
    ColorLightingDrawer() : ColorDrawer() {}
    ~ColorLightingDrawer() {}

    void Init();

protected:
    virtual void _Render() override;
};

class ColorMaterialDrawer : public ColorDrawer
{
public:
    ColorMaterialDrawer() : ColorDrawer() {}
    ~ColorMaterialDrawer() {}

    void Init();
    virtual void _Render() override;
};

struct MaterialData
{
    std::string name;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    MaterialData(std::string name, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
    {
        this->name = name;
        this->ambient = ambient;
        this->diffuse = diffuse;
        this->specular = specular;
    }
};

class ColorMaterialTableDrawer : public ColorDrawer
{
public:
    ColorMaterialTableDrawer();
    ~ColorMaterialTableDrawer();

    void Init();
    virtual void _Render() override;

private:
    std::vector<MaterialData> materials_;
};

#endif // !SRC_DRAWER_COLORDRAWER_H_
