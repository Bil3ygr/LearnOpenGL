#include "utils/public/texturemanager.h"

#include "utils/public/helper.h"
#include "glm/gtc/type_ptr.hpp"

TextureData* LoadImageFromFile(const char* filename)
{
    int width, height, nr_channels;
    stbi_set_flip_vertically_on_load(true);
    stbi_uc *data = stbi_load(filename, &width, &height, &nr_channels, 0);
    if (data)
    {
        return new TextureData(width, height, nr_channels, data);
    }
    else
    {
        ERROR("failed to load texture [%s]\n", filename);
        return nullptr;
    }
}

GLuint TextureManager::GetTexture(const std::string& filename)
{
    auto iter =  textures_.find(filename);
    if (iter != textures_.end())
    {
        return iter->second;
    }
    else
    {
        GLuint texture = CreateTexture(filename.c_str());
        textures_.emplace(filename, texture);
        return texture;
    }
}

void TextureManager::DeleteTexture(const std::string& filename)
{
    auto iter = textures_.find(filename);
    if (iter != textures_.end())
        textures_.erase(iter);
}

void TextureManager::DeleteTexture(const GLuint texture)
{
    for (auto iter = textures_.begin(); iter != textures_.end(); ++iter)
    {
        if (iter->second == texture)
        {
            glDeleteTextures(1, &texture);
            textures_.erase(iter);
        }
    }
}

void TextureManager::SetBorderColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    SetBorderColor(glm::vec4(r, g, b, a));
}

void TextureManager::SetBorderColor(glm::vec3 color)
{
    SetBorderColor(glm::vec4(color, 1.0f));
}

void TextureManager::SetBorderColor(glm::vec4 color)
{
    border_color_ = color;
}

TextureManager::TextureManager()
{
    textures_ = std::map<std::string, GLuint>();
    border_color_ = glm::vec4(1.0f);
}

TextureManager::~TextureManager()
{
    for (auto iter = textures_.begin(); iter != textures_.end(); ++iter)
        glDeleteTextures(1, &iter->second);
    textures_.clear();
}

GLuint TextureManager::CreateTexture(const char* filename)
{
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // 加载并生成纹理
    TextureData* data = LoadImageFromFile(filename);
    if (data)
    {
        // 为当前绑定的纹理对象设置环绕、过滤方式
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, data->WrapS());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, data->WrapT());
        if (data->WrapS() == GL_CLAMP_TO_BORDER || data->WrapT() == GL_CLAMP_TO_BORDER)
            glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, glm::value_ptr(border_color_));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, data->MinFilter());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, data->MaxFilter());

        glTexImage2D(GL_TEXTURE_2D, 0, data->ColorFormat(), data->width, data->height, 0, data->ColorFormat(), GL_UNSIGNED_BYTE, data->data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        texture = 0;
    }

    SAFE_DELETE(data)

    return texture;
}
