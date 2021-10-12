#pragma once

#ifndef SRC_DRAWER_SPACEDRAWER_H_
#define SRC_DRAWER_SPACEDRAWER_H_

#include <vector>

#include "basedrawer.h"
#include "camera/public/cameramanager.h"

class SpaceDrawer : public BaseDrawer
{
public:
    SpaceDrawer();
    virtual ~SpaceDrawer() override;

    void Init();

protected:
    virtual void _Render() override;

    std::vector<GLuint> textures_;
};

class SpaceDrawerCube : public SpaceDrawer
{
public:
    SpaceDrawerCube();
    ~SpaceDrawerCube() override final;

    void Init();

private:
    void _Render() override final;

    glm::mat4 GetModelWithTime(glm::mat4 model = glm::mat4(1.0f));
    glm::mat4 GetModelWithIndex(int index, glm::mat4 model = glm::mat4(1.0f));
    glm::mat4 GetViewStatic();
    glm::mat4 GetViewWithTime();

    SCamera camera_;
};

#endif // !SRC_DRAWER_SPACEDRAWER_H_
