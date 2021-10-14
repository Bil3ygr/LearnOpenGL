#include "scene/public/scenelightcaster.h"

#include "drawer/public/lightdrawer.h"
#include "drawer/public/lightcasterdrawer.h"

SceneLightcaster::SceneLightcaster() : Scene()
{
    dir_light_ = nullptr;
    point_light_ = nullptr;
    spot_light_ = nullptr;
    ui_ = nullptr;
}

SceneLightcaster::~SceneLightcaster()
{
    dir_light_ = nullptr;
    point_light_ = nullptr;
    spot_light_ = nullptr;
}

void SceneLightcaster::Enter()
{
    if (!dir_light_)
        dir_light_ = std::make_shared<DirLight>(glm::vec3(0.2f), glm::vec3(0.5f), glm::vec3(1.0f));

    if (!point_light_)
        point_light_ = std::make_shared<PointLight>(glm::vec3(0.2f), glm::vec3(0.5f), glm::vec3(1.0f));

    if (!spot_light_)
    {
        spot_light_ = std::make_shared<SpotLight>(glm::vec3(0.2f), glm::vec3(0.5f), glm::vec3(1.0f));
        spot_light_.get()->cutoff(glm::radians(12.5f));
        spot_light_.get()->outterCutoff(glm::radians(17.5f));
    }

    LightDrawer* light_drawer = new LightDrawer();
    light_drawer->Init();
    light_drawer->SetPointLight(point_light_);
    light_drawer->enable(false);
    AddDrawer(light_drawer);

    LightcasterDrawer* lightcaster_drawer = new LightcasterDrawer();
    lightcaster_drawer->Init();
    lightcaster_drawer->SetLight(dir_light_);
    lightcaster_drawer->enable(false);
    AddDrawer(lightcaster_drawer);

    LightcasterPointLightDrawer* pointlight_drawer = new LightcasterPointLightDrawer();
    pointlight_drawer->Init();
    pointlight_drawer->SetLight(point_light_);
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
    if (dir_light_)
        dir_light_.get()->ambient(value);
    if (point_light_)
        point_light_.get()->ambient(value);
    if (spot_light_)
        spot_light_.get()->ambient(value);
}

glm::vec3 SceneLightcaster::GetLightAmbient()
{
    if (dir_light_)
        return dir_light_.get()->ambient();
    else if (point_light_)
        return point_light_.get()->ambient();
    else if (spot_light_)
        return spot_light_.get()->ambient();
    return glm::vec3();
}

void SceneLightcaster::SetLightDiffuse(const glm::vec3& value)
{
    if (dir_light_)
        dir_light_.get()->diffuse(value);
    if (point_light_)
        point_light_.get()->diffuse(value);
    if (spot_light_)
        spot_light_.get()->diffuse(value);
}

glm::vec3 SceneLightcaster::GetLightDiffuse()
{
    if (dir_light_)
        return dir_light_.get()->diffuse();
    else if (point_light_)
        return point_light_.get()->diffuse();
    else if (spot_light_)
        return spot_light_.get()->diffuse();
    return glm::vec3();
}

void SceneLightcaster::SetLightSpecular(const glm::vec3& value)
{
    if (dir_light_)
        dir_light_.get()->specular(value);
    if (point_light_)
        point_light_.get()->specular(value);
    if (spot_light_)
        spot_light_.get()->specular(value);
}

glm::vec3 SceneLightcaster::GetLightSpecular()
{
    if (dir_light_)
        return dir_light_.get()->specular();
    else if (point_light_)
        return point_light_.get()->specular();
    else if (spot_light_)
        return spot_light_.get()->specular();
    return glm::vec3();
}

void SceneLightcaster::SetDirLightDirection(const glm::vec3& value)
{
    if (dir_light_)
        dir_light_.get()->direction(value);
}

glm::vec3 SceneLightcaster::GetDirLightDirection()
{
    if (dir_light_)
        return dir_light_.get()->direction();
    return glm::vec3();
}

void SceneLightcaster::SetPointLightPosition(const glm::vec3& value)
{
    if (point_light_)
        point_light_.get()->position(value);
}

glm::vec3 SceneLightcaster::GetPointLightPosition()
{
    if (point_light_)
        return point_light_.get()->position();
    return glm::vec3();
}

void SceneLightcaster::SetPointLightConstant(const float& value)
{
    if (point_light_)
        point_light_.get()->constant(value);
}

float SceneLightcaster::GetPointLightConstant()
{
    if (point_light_)
        return point_light_.get()->constant();
    return 1.0f;
}

void SceneLightcaster::SetPointLightLinear(const float& value)
{
    if (point_light_)
        point_light_.get()->linear(value);
}

float SceneLightcaster::GetPointLightLinear()
{
    if (point_light_)
        return point_light_.get()->linear();
    return 0.0f;
}

void SceneLightcaster::SetPointLightQuadratic(const float& value)
{
    if (point_light_)
        point_light_.get()->quadratic(value);
}

float SceneLightcaster::GetPointLightQuadratic()
{
    if (point_light_)
        return point_light_.get()->quadratic();
    return 0.0f;
}

void SceneLightcaster::SetSpotLightPosition(const glm::vec3& value)
{
    if (spot_light_)
        spot_light_.get()->position(value);
}

glm::vec3 SceneLightcaster::GetSpotLightPosition()
{
    if (spot_light_)
        return spot_light_.get()->position();
    return glm::vec3();
}

void SceneLightcaster::SetSpotLightDirection(const glm::vec3& value)
{
    if (spot_light_)
        spot_light_.get()->direction(value);
}

glm::vec3 SceneLightcaster::GetSpotLightDirection()
{
    if (spot_light_)
        return spot_light_.get()->direction();
    return glm::vec3();
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
        spot_light_.get()->outterCutoff(glm::radians(cutoff));
}

float SceneLightcaster::GetSpotLightOutterCutoff()
{
    if (spot_light_)
        return glm::degrees(spot_light_.get()->outterCutoff());
    return 0.0f;
}
