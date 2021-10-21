#pragma once

#ifndef SRC_NODE_TRIANGLE_H_
#define SRC_NODE_TRIANGLE_H_

#include <vector>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "basenode.h"

class Triangle : public BaseNode
{
public:
    Triangle(const std::string& name = "Node");
    ~Triangle();

    void Render();
    void Clear();

    VertexInfo& operator[](const int& idx);
    void update() { update_ = true; }

private:
    void PreRender();

    GLuint program_;
    GLuint vao_;
    bool update_;
    std::vector<VertexInfo> vertices_;
};

#endif // !SRC_NODE_TRIANGLE_H_
