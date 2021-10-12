#pragma once

#ifndef SRC_DRAWER_BASEDRAWER_H_
#define SRC_DRAWER_BASEDRAWER_H_

#include <string>

#include "glad/glad.h"
#include "glm/glm.hpp"

#include "drawerhelper.h"

class BaseDrawer
{
public:
    BaseDrawer();
    virtual ~BaseDrawer();

    void LinkDrawer(BaseDrawer* drawer);
    void UnlinkDrawer();

    void SetShader(const std::string& vsfile, const std::string& fsfile, const std::string& gsfile = "");

    void enable(const bool& _enable) { enable_ = _enable; }
    const bool enable() const { return enable_; }
    void pre_drawer(BaseDrawer* drawer) { pre_drawer_ = drawer; }
    BaseDrawer* pre_drawer() const { return pre_drawer_; }
    void next_drawer(BaseDrawer* drawer) { next_drawer_ = drawer; }
    BaseDrawer* next_drawer() const { return next_drawer_; }

    void depth_test(const bool& test)
    {
        if (test)
            glEnable(GL_DEPTH_TEST);
        else
            glDisable(GL_DEPTH_TEST);
    }

    void Render();

protected:
    virtual void _Render();

    GLuint program_;
    GLuint vao_;

private:
    bool enable_;
    BaseDrawer* pre_drawer_;
    BaseDrawer* next_drawer_;
};
#endif // !SRC_DRAWER_BASEDRAWER_H_
