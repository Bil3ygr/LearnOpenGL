#include "texture.h"

TextureNode::TextureNode(const std::string& name) : BaseNode(name)
{
    program_ = ShaderManager::Instance().GetShaderProgram("shader\\texture_vs.glsl", "shader\\texture_fs.glsl");
    vao_ = 0;
}

TextureNode::~TextureNode()
{

}

void TextureNode::Render()
{
    PreRender();

    if (!program_ || !vao_)
        return;

    glUseProgram(program_);
    glBindVertexArray(vao_);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    ShaderManager::Instance().SetBool(program_, "enable", false);

    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void TextureNode::Clear()
{

}

void TextureNode::SetTexture(const std::string& name)
{

}
