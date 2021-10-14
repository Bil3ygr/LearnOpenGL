#include "scene/public/scenelightmap.h"

#include "drawer/public/lightdrawer.h"
#include "drawer/public/lightmapdrawer.h"

SceneLightmap::SceneLightmap() : Scene()
{
    light_ = nullptr;
    ui_ = nullptr;
}

SceneLightmap::~SceneLightmap()
{
    light_ = nullptr;
}

void SceneLightmap::Enter()
{
    if (!light_)
    {
        light_ = std::make_shared<PointLight>(glm::vec3(0.2f), glm::vec3(0.5f), glm::vec3(1.0f));
        light_.get()->position(glm::vec3(1.2f, 1.0f, 2.0f));
    }

    LightDrawer* light_drawer = new LightDrawer();
    light_drawer->Init();
    light_drawer->SetPointLight(light_);
    AddDrawer(light_drawer);

    LightmapDrawer* lightmap_drawer = new LightmapDrawer();
    lightmap_drawer->Init();
    lightmap_drawer->SetLight(light_);
    AddDrawer(lightmap_drawer);

    if (ui_)
    {
        ERROR("UI already exists!");
        return;
    }
    ui_ = new LightmapUI();
}

void SceneLightmap::Leave()
{
    Scene::Leave();
    ui_->Close();
    SAFE_DELETE(ui_)
}

void SceneLightmap::SetLightAmbient(const glm::vec3& value)
{
    if (light_)
        light_.get()->ambient(value);
}

glm::vec3 SceneLightmap::GetLightAmbient()
{
    if (light_)
        return light_.get()->ambient();
    return glm::vec3();
}

void SceneLightmap::SetLightDiffuse(const glm::vec3& value)
{
    if (light_)
        light_.get()->diffuse(value);
}

glm::vec3 SceneLightmap::GetLightDiffuse()
{
    if (light_)
        return light_.get()->diffuse();
    return glm::vec3();
}

void SceneLightmap::SetLightSpecular(const glm::vec3& value)
{
    if (light_)
        light_.get()->specular(value);
}

glm::vec3 SceneLightmap::GetLightSpecular()
{
    if (light_)
        return light_.get()->specular();
    return glm::vec3();
}
