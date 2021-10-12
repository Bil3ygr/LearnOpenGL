#include "scene/public/scenedefault.h"

#include "glm/glm.hpp"

#include "utils/public/helper.h"

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
