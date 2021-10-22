#include "texturenode.h"

#include "render/shadermanager.h"
#include "render/texturemanager.h"
#include "drawer/drawerhelper.h"

TextureNode::TextureNode(const std::string& name) : BaseNode(name)
{
    program_ = ShaderManager::Instance().GetShaderProgram("shader\\texture_vs.glsl", "shader\\texture_fs.glsl");
    vao_ = 0;
    texture_ = 0;
    color_ = glm::vec4(1.0f);
}

TextureNode::~TextureNode()
{
    glDeleteVertexArrays(1, &vao_);
}

void TextureNode::Render()
{
    PreRender();

    if (!program_ || !vao_ || !texture_)
        return;

    glUseProgram(program_);
    glBindVertexArray(vao_);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    ShaderManager::Instance().SetBool(program_, "mixEnable", false);
    ShaderManager::Instance().SetInt(program_, "texture0", 0);
    ShaderManager::Instance().SetVec4(program_, "mixColor", color_);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void TextureNode::Clear()
{
    texture_ = 0;
}

void TextureNode::SetTexture(const std::string& name)
{
    texture_ = TextureManager::Instance().GetTexture(name);
}

void TextureNode::PreRender()
{
    if (!vao_)
    {
        float vertices[] = {
            // ---- 位置 ---  - 纹理坐标 -
            1.0f, 1.0f, 0.0f, 1.0f, 1.0f,  // 右上
            1.0f, 0.0f, 0.0f, 1.0f, 0.0f,  // 右下
            0.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // 左下
            0.0f, 1.0f, 0.0f, 0.0f, 1.0f,  // 左上
        };
        int pointers[] = { 3, 2 };
        int indices[] = {
            0, 3, 1,
            3, 2, 1,
        };
        vao_ = DrawerHelper::GetVertexArrayObject(vertices, sizeof(vertices), pointers, 2, indices, sizeof(indices));
    }
}
