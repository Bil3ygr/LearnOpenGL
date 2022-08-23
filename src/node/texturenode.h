#pragma once

#ifndef SRC_NODE_TEXTURENODE_H_
#define SRC_NODE_TEXTURENODE_H_

#include "glad/glad.h"

#include "basenode.h"

class TextureNode : public BaseNode
{
public:
    TextureNode(const std::string& name = "Node");
    ~TextureNode();

    virtual void Render();
    virtual void Clear();

    void SetTexture(const std::string& filename);

protected:
    void PreRender();

    GLuint program_;
    GLuint vao_;
    glm::vec4 color_;

private:
    GLuint texture_;
};

class MixTextureNode : public TextureNode
{
public:
    MixTextureNode(const std::string& name = "Node");
    ~MixTextureNode();

    void Render();
    void Clear();

    void SetTexture0(const std::string& filename);
    void SetTexture1(const std::string& filename);

private:
    GLuint texture0_;
    GLuint texture1_;
};

#endif // !SRC_NODE_TEXTURENODE_H_
