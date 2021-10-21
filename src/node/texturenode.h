#pragma once

#ifndef SRC_NODE_TEXTURENODE_H_
#define SRC_NODE_TEXTURENODE_H_

#include "basenode.h"

class TextureNode : public BaseNode
{
public:
    TextureNode(const std::string& name = "Node");
    ~TextureNode();

    void Render();
    void Clear();

    void SetTexture(const std::string& filename);

private:
    GLuint program_;
    GLuint vao_;
};

#endif // !SRC_NODE_TEXTURENODE_H_
