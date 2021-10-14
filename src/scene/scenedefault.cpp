#include "scene/scenedefault.h"

#include "glm/glm.hpp"

#include "utils/helper.h"

SceneDefault::~SceneDefault()
{
}

void SceneDefault::Enter()
{
    BaseDrawer* drawer = new BaseDrawer();
    AddDrawer(drawer);

    if (ui_)
    {
        ERROR("UI already exists!");
        return;
    }
    ui_ = new DefaultUI();
}

void SceneDefault::Leave()
{
    Scene::Leave();
    ui_->Close();
    SAFE_DELETE(ui_)
}
