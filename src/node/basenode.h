#pragma once

#ifndef SRC_NODE_BASENODE_H_
#define SRC_NODE_BASENODE_H_

#include <string>
#include <vector>

#include "common/transform.h"

struct VertexInfo
{
    glm::vec3 vertex;
    glm::vec4 color;

    VertexInfo() : vertex(glm::vec3()), color(glm::vec4(1.0f)) {}
    VertexInfo(glm::vec3 _vertex, glm::vec4 _color) : vertex(_vertex), color(_color) {}

    VertexInfo& operator=(const VertexInfo& t_vertex)
    {
        vertex = t_vertex.vertex;
        color = t_vertex.color;
        return *this;
    }
};

class BaseNode
{
public:
    BaseNode(const std::string& name = "Node");
    ~BaseNode();

    void AddChild(BaseNode* child);
    bool DeleteChild(BaseNode* child);
    std::vector<BaseNode*> GetChildren() const { return children_; }

    void SetParent(BaseNode* parent);
    BaseNode* GetParent() { return parent_; }

    void Draw();
    virtual void Render();

public:
    void name(const std::string& name) { name_ = name; }
    std::string name() const { return name_; }
    void visible(const bool& visible) { visible_ = visible; }
    bool visible() const { return visible_; }

    void transform(Transform* transform) { transform_ = transform; }
    Transform* transform() { return new Transform(*transform_); }

private:
    std::string name_;
    BaseNode* parent_;
    std::vector<BaseNode*> children_;

    bool visible_;
    Transform* transform_;
};

#endif // !SRC_NODE_BASENODE_H_
