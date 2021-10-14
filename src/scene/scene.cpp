#include "scene/scene.h"

Scene::Scene()
{
    drawers_ = std::vector<BaseDrawer*>();
    color_ = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
}

Scene::~Scene()
{
    Leave();
}

void Scene::Render()
{
    glClearColor(color_.r, color_.g, color_.b, color_.a);
    glClear(GL_COLOR_BUFFER_BIT);

    if (!drawers_.empty())
        drawers_[0]->Render();

    UIManager::Instance().Render();
}

void Scene::Enter()
{
}

void Scene::Leave()
{
    for (auto drawer : drawers_)
        delete drawer;
    drawers_.clear();
}

void Scene::AddDrawer(BaseDrawer* drawer)
{
    if (!drawers_.empty())
    {
        BaseDrawer* last_drawer = *drawers_.rbegin();
        last_drawer->LinkDrawer(drawer);
    }
    drawers_.emplace_back(drawer);
}

// void Scene::ClearColor()
// {
//     glClearColor(color_.r, color_.g, color_.b, color_.a);
//     glClear(GL_COLOR_BUFFER_BIT);

//     // GLbitfield mask = GL_COLOR_BUFFER_BIT;
//     // if (depth_test_)
//     //     mask |= GL_DEPTH_BUFFER_BIT;
// }
