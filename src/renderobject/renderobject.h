#pragma once

#ifndef SRC_RENDEROBJECT_RENDEROBJECT_H_
#define SRC_RENDEROBJECT_RENDEROBJECT_H_

#include <vector>

#include "common/transform.h"

class RenderObject
{
public:
    RenderObject();
    ~RenderObject();

    void AddChild(RenderObject* child);
    bool DeleteChild(RenderObject* child);
    std::vector<RenderObject*> GetChildren() const { return children_; }

    void SetParent(RenderObject* parent);
    RenderObject* GetParent() { return parent_; }

    void Draw();
    virtual void Render() = 0;

public:
    void visible(const bool& visible) { visible_ = visible; }
    bool visible() const { return visible_; }

    void transform(Transform* transform) { transform_ = transform; }
    Transform* transform() { return new Transform(*transform_); }

private:
    RenderObject* parent_;
    std::vector<RenderObject*> children_;

    bool visible_;
    Transform* transform_;
};

#endif // !SRC_RENDEROBJECT_RENDEROBJECT_H_
