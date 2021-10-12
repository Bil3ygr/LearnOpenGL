#include "scene/public/scenelightmap.h"

#include "drawer/public/lightdrawer.h"
#include "drawer/public/lightmapdrawer.h"

SceneLightmap::SceneLightmap() : Scene()
{
    light_ = nullptr;
}

SceneLightmap::~SceneLightmap()
{
    light_ = nullptr;
}

void SceneLightmap::Enter()
{
    if (!light_)
        light_ = std::make_shared<Light>(glm::vec3(0.2f), glm::vec3(0.5f), glm::vec3(1.0f));

    LightDrawer* light_drawer = new LightDrawer();
    light_drawer->Init();
    light_drawer->SetLight(light_);
    AddDrawer(light_drawer);

    LightmapDrawer* lightmap_drawer = new LightmapDrawer();
    lightmap_drawer->Init();
    lightmap_drawer->SetLight(light_);
    AddDrawer(lightmap_drawer);
}
