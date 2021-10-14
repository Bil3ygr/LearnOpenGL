#include "drawer/texturedrawer.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "GLFW/glfw3.h"

#include "utils/helper.h"
#include "utils/shadermanager.h"
#include "utils/texturemanager.h"

TextureDrawer::TextureDrawer() : BaseDrawer()
{
    textures_ = std::vector<GLuint>();
}

TextureDrawer::~TextureDrawer()
{
    glDisable(GL_DEPTH_TEST);
    if (!textures_.empty())
        textures_.clear();
}

void TextureDrawer::Init()
{
    glEnable(GL_DEPTH_TEST);

    SetShader("shader\\texture_vs.glsl", "shader\\texture_fs.glsl");

    float vertices[] = {
        //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
        1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,	  // 右上
        1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // 右下
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // 左下
        0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f	  // 左上
    };
    int pointers[] = { 3, 3, 2 };
    int indices[] = {
       0, 3, 1,
       3, 2, 1,
    };
    vao_ = DrawerHelper::GetVertexArrayObject(
        vertices, sizeof(vertices),
        pointers, sizeof(pointers) / sizeof(pointers[0]),
        indices, sizeof(indices)
    );

    textures_.emplace_back(TextureManager::Instance().GetTexture("res\\container.jpg"));
    textures_.emplace_back(TextureManager::Instance().GetTexture("res\\93365078_p1_master1200.png"));
}

void TextureDrawer::_Render()
{
    glClear(GL_DEPTH_BUFFER_BIT);

    glUseProgram(program_);
    glBindVertexArray(vao_);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    {
        for (int i = 0; i < textures_.size(); ++i)
        {
            ShaderManager::Instance().SetInt(program_, "texture" + TO_STR(i), i);
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, textures_[i]);
        }
        ShaderManager::Instance().SetFloat(program_, "mixValue", mix_value_);
    }
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void TextureDrawerTransformation::Init()
{
    glEnable(GL_DEPTH_TEST);

    SetShader("shader\\texture_transformation_vs.glsl", "shader\\texture_fs.glsl");

    float vertices[] = {
        //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,	  // 右上
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // 右下
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // 左下
        -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f	  // 左上
    };
    int pointers[] = { 3, 3, 2 };
    int indices[] = {
       0, 3, 1,
       3, 2, 1,
    };
    vao_ = DrawerHelper::GetVertexArrayObject(
        vertices, sizeof(vertices),
        pointers, sizeof(pointers) / sizeof(pointers[0]),
        indices, sizeof(indices)
    );

    textures_.emplace_back(TextureManager::Instance().GetTexture("res\\container.jpg"));
    textures_.emplace_back(TextureManager::Instance().GetTexture("res\\awesomeface.png"));
}

void TextureDrawerTransformation::_Render()
{
    glClear(GL_DEPTH_BUFFER_BIT);

    glUseProgram(program_);
    glBindVertexArray(vao_);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    for (int i = 0; i < textures_.size(); ++i)
    {
        ShaderManager::Instance().SetInt(program_, "texture" + TO_STR(i), i);
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, textures_[i]);
    }

    {
        float radian;
        if (auto_rotate_)
            radian = (float)glfwGetTime() * speed_;
        else
            radian = radian_;
        // transformation
        glm::mat4 trans(1.0f);
        trans = glm::translate(trans, glm::vec3(-0.5f, 0.5f, 0.0f));
        trans = glm::rotate(trans, radian, glm::vec3(0.0f, 0.0f, 1.0f));
        //trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        trans = glm::scale(trans, glm::vec3(0.5f));
        ShaderManager::Instance().SetMat4(program_, "transform", trans);
    }
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // practice
    {
        // transformation
        glm::mat4 trans(1.0f);
        trans = glm::translate(trans, glm::vec3(-0.5f, -0.5f, 0.0f));
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        // trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        // trans = glm::scale(trans, glm::vec3(abs(sin(glfwGetTime()))));
        trans = glm::scale(trans, scale_);
        ShaderManager::Instance().SetMat4(program_, "transform", trans);
    }
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
