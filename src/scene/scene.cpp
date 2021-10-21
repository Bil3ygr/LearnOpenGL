#include "scene.h"

Scene::Scene()
{
    drawers_ = std::vector<BaseDrawer*>();
    color_ = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    nodes_ = std::vector<BaseNode*>();
    root_ = new BaseNode();
}

Scene::~Scene()
{
    Leave();
}

void Scene::Render()
{
    glClearColor(color_.r, color_.g, color_.b, color_.a);
    glClear(GL_COLOR_BUFFER_BIT);

    root_->Draw();
}

void Scene::Enter()
{
}

void Scene::Leave()
{
    SAFE_DELETE(root_)
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

void Scene::AddNode(BaseNode* node)
{
    if (!node->GetParent())
        root_->AddChild(node);

    nodes_.emplace_back(node);
}

void Scene::DeleteNode(BaseNode* node)
{
    if (node->GetParent() == root_)
        root_->DeleteChild(node);

    if (!nodes_.empty())
        nodes_.erase(std::remove(nodes_.begin(), nodes_.end(), node), nodes_.end());
}

const BaseNode* Scene::FindNodeByName(const std::string& name)
{
    for (BaseNode* node : nodes_)
        if (node->name() == name)
            return node;
    return nullptr;
}

std::vector<BaseNode> Scene::FindNodesByName(const std::string& name)
{
    std::vector<BaseNode> ret = std::vector<BaseNode>();
    for (BaseNode* node : nodes_)
        if (node->name() == name)
            ret.emplace_back(*node);
    return ret;
}
