#pragma once

#ifndef SRC_DRAWER_TEXTUREDRAWER_H_
#define SRC_DRAWER_TEXTUREDRAWER_H_

#include <vector>

#include "basedrawer.h"

class TextureDrawer : public BaseDrawer
{
public:
    TextureDrawer();
    ~TextureDrawer() override;

    void Init();

    void mixValue(const float& value) { mix_value_ = value; }

protected:
    virtual void _Render() override;

    std::vector<GLuint> textures_;
    float mix_value_ = 0.2f;
};

class TextureDrawerTransformation : public TextureDrawer
{
public:
    void Init();

    void autoRotate(const bool& auto_rotate) { auto_rotate_ = auto_rotate; }
    void rotateSpeed(const float& speed) { speed_ = speed; }
    void rotateRadian(const float& radian) { radian_ = radian; }
    void scale(const glm::vec3& _scale) { scale_ = _scale; }

protected:
    void _Render() override final;
    bool auto_rotate_ = true;
    float speed_ = 1.0f;
    float radian_ = 0.0f;
    glm::vec3 scale_ = glm::vec3(1.0f);
};

#endif // !SRC_DRAWER_TEXTUREDRAWER_H_
