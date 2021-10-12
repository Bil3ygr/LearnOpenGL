#include "scene/public/scenecolor.h"

#include "drawer/public/colordrawer.h"
#include "drawer/public/lightdrawer.h"

SceneColor::SceneColor() : Scene()
{
    light_ = nullptr;
    ui_ = nullptr;
}

SceneColor::~SceneColor()
{
    light_ = nullptr;
}

void SceneColor::Enter()
{
    if (!light_)
        light_ = std::make_shared<Light>(glm::vec3(0.2f), glm::vec3(0.5f), glm::vec3(1.0f));

    LightDrawer* light_drawer = new LightDrawer();
    light_drawer->Init();
    light_drawer->SetLight(light_);
    AddDrawer(light_drawer);

    ColorDrawer* color_drawer = new ColorDrawer();
    color_drawer->Init();
    color_drawer->enable(false);
    AddDrawer(color_drawer);

    ColorLightingDrawer* lighting_drawer = new ColorLightingDrawer();
    lighting_drawer->Init();
    lighting_drawer->SetLight(light_);
    lighting_drawer->enable(false);
    AddDrawer(lighting_drawer);

    ColorMaterialDrawer* material_drawer = new ColorMaterialDrawer();
    material_drawer->Init();
    material_drawer->SetLight(light_);
    AddDrawer(material_drawer);

    ColorMaterialTableDrawer* material_table_drawer = new ColorMaterialTableDrawer();
    material_table_drawer->Init();
    material_table_drawer->SetLight(light_);
    material_table_drawer->enable(false);
    AddDrawer(material_table_drawer);

    if (ui_)
    {
        ERROR("UI already exists!");
        return;
    }
    ui_ = new ColorUI();
}

void SceneColor::Leave()
{
    Scene::Leave();
    ui_->Close();
    SAFE_DELETE(ui_)
}
