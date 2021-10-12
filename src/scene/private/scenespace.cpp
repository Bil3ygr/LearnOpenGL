#include "scene/public/scenespace.h"

#include "drawer/public/spacedrawer.h"

SceneSpace::~SceneSpace()
{
}

void SceneSpace::Enter()
{
    SpaceDrawer* space_drawer = new SpaceDrawer();
    space_drawer->Init();
    space_drawer->enable(false);
    AddDrawer(space_drawer);

    SpaceDrawerCube* cube_drawer = new SpaceDrawerCube();
    cube_drawer->Init();
    AddDrawer(cube_drawer);

    if (ui_)
    {
        ERROR("UI already exists!");
        return;
    }
    ui_ = new SpaceUI();
}

void SceneSpace::Leave()
{
    Scene::Leave();
    ui_->Close();
    SAFE_DELETE(ui_)
}
