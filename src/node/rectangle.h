#pragma once

#ifndef SRC_NODE_RECTANGLE_H_
#define SRC_NODE_RECTANGLE_H_

#include <vector>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "basenode.h"

class Rectangle : public BaseNode
{
public:
    Rectangle(const std::string& name = "Node");
    ~Rectangle();

    void Render();
    void Clear();

    VertexInfo& operator[](const int& idx);
    void update() { update_ = true; }
    void line_mode(const bool& mode) { line_mode_ = mode; }
    bool line_mode() const { return line_mode_; }

private:
    void PreRender();

    GLuint program_;
    GLuint vao_;
    bool update_;
    std::vector<VertexInfo> vertices_;
    bool line_mode_;
};

#endif // !SRC_NODE_RECTANGLE_H_
