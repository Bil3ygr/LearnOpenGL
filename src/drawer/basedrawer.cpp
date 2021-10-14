#include "drawer/basedrawer.h"

#include "utils/shadermanager.h"
#include "utils/helper.h"

BaseDrawer::BaseDrawer()
{
    program_ = 0;
    vao_ = 0;
    enable_ = true;
    pre_drawer_ = nullptr;
    next_drawer_ = nullptr;
}

BaseDrawer::~BaseDrawer()
{
    if (program_)
    {
        glDeleteProgram(program_);
    }

    if (vao_)
    {
        glDeleteVertexArrays(1, &vao_);
        vao_ = 0;
    }
}

void BaseDrawer::LinkDrawer(BaseDrawer* drawer)
{
    if (next_drawer())
    {
        ERROR("currant drawer already has next drawer, link failed\n");
        return;
    }
    else if (drawer->pre_drawer())
    {
        ERROR("linked drawer already has pre drawer, link failed\n");
        return;
    }

    next_drawer(drawer);
    drawer->pre_drawer(this);
}

void BaseDrawer::UnlinkDrawer()
{
    BaseDrawer* temp = nullptr;
    if (next_drawer())
    {
        temp = next_drawer();
        next_drawer(nullptr);
        temp->pre_drawer(nullptr);
    }

    if (pre_drawer())
    {
        pre_drawer()->next_drawer(temp);
        if (temp)
            temp->pre_drawer(pre_drawer());
        pre_drawer(nullptr);
    }
}

void BaseDrawer::SetShader(const std::string& vsfile, const std::string& fsfile, const std::string& gsfile)
{
    program_ = ShaderManager::Instance().GetShaderProgram(vsfile, fsfile, gsfile);
}

void BaseDrawer::Render()
{
    if (enable_)
        _Render();

    if (next_drawer())
        next_drawer()->Render();
}

void BaseDrawer::_Render()
{
    glDisable(GL_DEPTH_TEST);
}
