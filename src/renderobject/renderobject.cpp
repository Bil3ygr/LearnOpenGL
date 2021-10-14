#include "renderobject/renderobject.h"

#include <algorithm>

RenderObject::RenderObject()
{
    parent_ = nullptr;
    children_ = std::vector<RenderObject*>();

    visible_ = true;
}

RenderObject::~RenderObject()
{
    if (parent_)
        parent_->DeleteChild(this);
    for (RenderObject* child : children_)
        DeleteChild(child);
    children_.clear();
}

void RenderObject::AddChild(RenderObject* child)
{
    if (!child)
        return;

    children_.emplace_back(child);
    child->SetParent(this);
}

bool RenderObject::DeleteChild(RenderObject* child)
{
    if (!child)
        return false;

    if (!children_.empty())
    {
        children_.erase(std::remove(children_.begin(), children_.end(), child), children_.end());
        child->SetParent(nullptr);
        return true;
    }
    return false;
}

void RenderObject::SetParent(RenderObject* parent)
{
    if (parent_ == parent)
        return;

    if (parent_)
    {
        RenderObject* old_parent = parent_;
        parent_ = nullptr;
        old_parent->DeleteChild(this);
    }

    parent_ = parent;
    if (parent_)
        parent_->AddChild(this);
}

void RenderObject::Draw()
{
    if (!visible())
        return;

    Render();

    for (RenderObject* child : children_)
        child->Draw();
}
