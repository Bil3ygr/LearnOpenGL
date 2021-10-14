#include "scene/scenetriangle.h"

#include "utils/helper.h"
#include "drawer/triangledrawer.h"
#include "drawer/rectdrawer.h"

SceneTriangle::~SceneTriangle()
{
}

void SceneTriangle::Enter()
{
    // TriangleDrawer* drawer = new TriangleDrawer();
    TriangleDrawer* drawer = new TriangleDrawerWithTimeColor();
    drawer->Init();
    AddDrawer(drawer);

    drawer = new TriangleDrawerPractice();
    drawer->Init();
    AddDrawer(drawer);

    // drawer = new TriangleDrawerWithInitColor();
    drawer = new TriangleDrawerWithInitColorPractice();
    drawer->Init();
    AddDrawer(drawer);

    RectDrawer* rect_drawer = new RectDrawer();
    rect_drawer->Init();
    AddDrawer(rect_drawer);

    if (ui_)
    {
        ERROR("UI already exists!");
        return;
    }
    ui_ = new TriangleUI();
}

void SceneTriangle::Leave()
{
    Scene::Leave();
    ui_->Close();
    SAFE_DELETE(ui_)
}

void SceneTriangle::rectLine(const bool& is_line)
{
    if (rect_line_ == is_line)
        return;

    rect_line_ = is_line;
    for (auto drawer : drawers_)
    {
        RectDrawer* _drawer = dynamic_cast<RectDrawer*>(drawer);
        if (_drawer)
            _drawer->isLine(is_line);
    }
}
