#pragma once

#ifndef SRC_UTILS_TEXTUREMANAGER_H_
#define SRC_UTILS_TEXTUREMANAGER_H_

#include <string>
#include <map>
#include <vector>

#include "glad/glad.h"
#include "glm/glm.hpp"

#include "utils/helper.h"
#include "utils/singleton.h"
#include "utils/stb_image.h"

struct TextureData
{
    int width;
    int height;
    int nr_channels;
    stbi_uc* data;

    TextureData(int _width, int _height, int _nr_channels, stbi_uc* _data) :
        width(_width), height(_height), nr_channels(_nr_channels), data(_data) {}

    ~TextureData() { stbi_image_free(data); }

    GLint ColorFormat()
    {
        switch (nr_channels)
        {
        case 1:
            return GL_RED;
        case 4:
            return GL_RGBA;
        default:
            return GL_RGB;
        }
    }

    GLint WrapS()
    {
        switch (nr_channels)
        {
        case 4:
            return GL_CLAMP_TO_EDGE;
        default:
            return GL_REPEAT;
        }
    }

    GLint WrapT()
    {
        switch (nr_channels)
        {
        case 4:
            return GL_CLAMP_TO_EDGE;
        default:
            return GL_REPEAT;
        }
    }

    GLint MinFilter()
    {
        return GL_LINEAR;
    }

    GLint MaxFilter()
    {
        return GL_LINEAR;
    }
};

TextureData* LoadImageFromFile(const char* filename);

class TextureManager : public Singleton<TextureManager>
{
    friend class Singleton<TextureManager>;
public:
    GLuint GetTexture(const std::string& filename);
    void DeleteTexture(const std::string& filename);
    void DeleteTexture(const GLuint texture);

    void SetBorderColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0f);
    void SetBorderColor(glm::vec3 color);
    void SetBorderColor(glm::vec4 color);

private:
    TextureManager();
    ~TextureManager();

    GLuint CreateTexture(const char* filename);

    std::map<std::string, GLuint> textures_;
    glm::vec4 border_color_;
};
#endif // !SRC_UTILS_TEXTUREMANAGER_H_
