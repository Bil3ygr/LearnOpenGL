#pragma once

#ifndef SRC_RENDEROBJECT_TRIANGLEOBJECT_H_
#define SRC_RENDEROBJECT_TRIANGLEOBJECT_H_

#include "renderobject.h"

#include <vector>

class TriangleObject : public RenderObject
{
public:
    TriangleObject();
    ~TriangleObject();

    void Render();

public:
    void PreRender();

    void AddPoints();

private:
    std::vector<glm::vec3> vertices_;
    std::vector<glm::vec3> colors_;
};

#endif // !SRC_RENDEROBJECT_TRIANGLEOBJECT_H_
