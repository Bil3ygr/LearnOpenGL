#include "basenode.h"

#include <algorithm>

BaseNode::BaseNode(const std::string& name)
{
    name_ = name;
    parent_ = nullptr;
    children_ = std::vector<BaseNode*>();

    visible_ = true;
}

BaseNode::~BaseNode()
{
    if (parent_)
        parent_->DeleteChild(this);
    for (BaseNode* child : children_)
        DeleteChild(child);
    children_.clear();
}

void BaseNode::AddChild(BaseNode* child)
{
    if (!child)
        return;

    for (auto _child : children_)
        if (_child == child)
            return;

    children_.emplace_back(child);
    child->SetParent(this);
}

bool BaseNode::DeleteChild(BaseNode* child)
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

void BaseNode::SetParent(BaseNode* parent)
{
    if (parent_ == parent)
        return;

    if (parent_)
    {
        BaseNode* old_parent = parent_;
        parent_ = nullptr;
        old_parent->DeleteChild(this);
    }

    parent_ = parent;
    if (parent_)
        parent_->AddChild(this);
}

void BaseNode::Draw()
{
    if (!visible())
        return;

    Render();

    for (BaseNode* child : children_)
        child->Draw();
}

void BaseNode::Render()
{
}
