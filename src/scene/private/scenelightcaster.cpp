#include "scene/public/scenelightcaster.h"

#include "drawer/public/lightdrawer.h"
#include "drawer/public/lightcasterdrawer.h"

SceneLightcaster::SceneLightcaster() : Scene()
{
    light_ = nullptr;
    spot_light_ = nullptr;
    ui_ = nullptr;
}

SceneLightcaster::~SceneLightcaster()
{
    light_ = nullptr;
    spot_light_ = nullptr;
}

void SceneLightcaster::Enter()
{
    if (!light_)
        light_ = std::make_shared<Light>(
            glm::vec3(0.2f), glm::vec3(0.5f), glm::vec3(1.0f), glm::vec4(glm::vec3(), 1.0f));

    if (!spot_light_)
    {
        spot_light_ = std::make_shared<SpotLight>();
        spot_light_.get()->ambient(glm::vec3(0.2f));
        spot_light_.get()->diffuse(glm::vec3(0.5f));
        spot_light_.get()->specular(glm::vec3(1.0f));
        spot_light_.get()->cutoff(glm::radians(12.5f));
        spot_light_.get()->outtercutoff(glm::radians(17.5f));
    }

    LightDrawer* light_drawer = new LightDrawer();
    light_drawer->Init();
    light_drawer->SetLight(light_);
    AddDrawer(light_drawer);

    LightcasterDrawer* lightcaster_drawer = new LightcasterDrawer();
    lightcaster_drawer->Init();
    lightcaster_drawer->SetLight(light_);
    lightcaster_drawer->enable(false);
    AddDrawer(lightcaster_drawer);

    LightcasterPointLightDrawer* pointlight_drawer = new LightcasterPointLightDrawer();
    pointlight_drawer->Init();
    pointlight_drawer->SetLight(light_);
    pointlight_drawer->enable(false);
    AddDrawer(pointlight_drawer);

    LightcasterSpotLightDrawer* spotlight_drawer = new LightcasterSpotLightDrawer();
    spotlight_drawer->Init();
    spotlight_drawer->SetLight(spot_light_);
    AddDrawer(spotlight_drawer);

    if (ui_)
    {
        ERROR("UI already exists!");
        return;
    }
    ui_ = new LightcasterUI();
}

void SceneLightcaster::Leave()
{
    Scene::Leave();
    ui_->Close();
    SAFE_DELETE(ui_)
}

void SceneLightcaster::SetLightAmbient(const glm::vec3& value)
{
    if (light_)
        light_.get()->ambient(value);
}

glm::vec3 SceneLightcaster::GetLightAmbient()
{
    if (light_)
        return light_.get()->ambient();
    return glm::vec3();
}

void SceneLightcaster::SetLightDiffuse(const glm::vec3& value)
{
    if (light_)
        light_.get()->diffuse(value);
}

glm::vec3 SceneLightcaster::GetLightDiffuse()
{
    if (light_)
        return light_.get()->diffuse();
    return glm::vec3();
}

void SceneLightcaster::SetLightSpecular(const glm::vec3& value)
{
    if (light_)
        light_.get()->specular(value);
}

glm::vec3 SceneLightcaster::GetLightSpecular()
{
    if (light_)
        return light_.get()->specular();
    return glm::vec3();
}

void SceneLightcaster::SetLightVector3(const glm::vec3& value)
{
    if (light_)
    {
        float w = light_.get()->vector().w;
        light_.get()->vector(glm::vec4(value, w));
    }
}

glm::vec3 SceneLightcaster::GetLightVector3()
{
    if (light_)
        return light_.get()->vector();
    return glm::vec3();
}

void SceneLightcaster::SetIsPointLight(const bool& check)
{
    if (light_)
    {
        glm::vec4 vec = light_.get()->vector();
        vec.w = check ? 1.0f : 0.0f;
        light_.get()->vector(vec);
    }
}

bool SceneLightcaster::IsPointLight()
{
    if (light_)
    {
        glm::vec4 vec = light_.get()->vector();
        return vec.w == 1.0f ? true : false;
    }
    return false;
}

void SceneLightcaster::SetSpotLightCutoff(const float& cutoff)
{
    if (spot_light_)
        spot_light_.get()->cutoff(glm::radians(cutoff));
}

float SceneLightcaster::GetSpotLightCutoff()
{
    if (spot_light_)
        return glm::degrees(spot_light_.get()->cutoff());
    return 0.0f;
}

void SceneLightcaster::SetSpotLightOutterCutoff(const float& cutoff)
{
    if (spot_light_)
        spot_light_.get()->outtercutoff(glm::radians(cutoff));
}

float SceneLightcaster::GetSpotLightOutterCutoff()
{
    if (spot_light_)
        return glm::degrees(spot_light_.get()->outtercutoff());
    return 0.0f;
}
