#pragma once

#ifndef SRC_UI_BASEUI_H_
#define SRC_UI_BASEUI_H_

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class BaseUI
{
public:
    BaseUI();
    ~BaseUI();

    virtual void Render() = 0;
    void Close();

    void visible(const bool& _visible) { visible_ = _visible; }
    const bool visible() const { return visible_; }
    const boost::uuids::uuid uuid() const { return tag_; }

private:
    bool visible_ = true;
    boost::uuids::uuid tag_;
};

#endif // !SRC_UI_BASEUI_H_
