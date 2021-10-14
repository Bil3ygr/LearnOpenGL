#include "drawer/spacedrawer.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "GLFW/glfw3.h"

#include "utils/consts.h"
#include "utils/shadermanager.h"
#include "utils/texturemanager.h"
#include "utils/mousemanager.h"

SpaceDrawer::SpaceDrawer() : BaseDrawer()
{
    textures_ = std::vector<GLuint>();
}

SpaceDrawer::~SpaceDrawer()
{
    glDisable(GL_DEPTH_TEST);
    if (!textures_.empty())
        textures_.clear();
}

void SpaceDrawer::Init()
{
    glEnable(GL_DEPTH_TEST);

    SetShader("shader\\space_vs.glsl", "shader\\texture_fs.glsl");

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

void SpaceDrawer::_Render()
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

        glm::mat4 model(1.0f);
        model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        glm::mat4 view(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        glm::mat4 projection(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float)(WITDH / HEIGHT), 0.1f, 100.0f);
        ShaderManager::Instance().SetMat4(program_, "model", model);
        ShaderManager::Instance().SetMat4(program_, "view", view);
        ShaderManager::Instance().SetMat4(program_, "projection", projection);
    }
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

SpaceDrawerCube::SpaceDrawerCube() : SpaceDrawer()
{
    camera_ = CameraManager::Instance().GetDefaultCamera();
    if (!camera_)
        camera_ = CameraManager::Instance().CreateCamera(0);
    MouseManager::Instance().buttonEnable(true);
}

SpaceDrawerCube::~SpaceDrawerCube()
{
    glDisable(GL_DEPTH_TEST);
    camera_ = nullptr;
    MouseManager::Instance().buttonEnable(false);
}

void SpaceDrawerCube::Init()
{
    glEnable(GL_DEPTH_TEST);

    SetShader("shader\\space_cube_vs.glsl", "shader\\texture_fs.glsl");

    camera_.get()->SetProgram(program_);

    int pointers[] = { 3, 2 };
    vao_ = DrawerHelper::GetVertexArrayObject(
        array_cube_texture, sizeof(array_cube_texture),
        pointers, sizeof(pointers) / sizeof(pointers[0])
    );

    textures_.emplace_back(TextureManager::Instance().GetTexture("res\\container.jpg"));
    textures_.emplace_back(TextureManager::Instance().GetTexture("res\\awesomeface.png"));
}

void SpaceDrawerCube::_Render()
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

        glm::mat4 model = GetModelWithTime();
        ShaderManager::Instance().SetMat4(program_, "model", model);

        // glm::mat4 view = GetViewStatic();
        // glm::mat4 view = GetViewWithTime();
        // ShaderManager::Instance().SetMat4(program_, "view", view);
        //camera_.get()->Update(GetViewWithTime());
        camera_.get()->Update();

        // glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)(WITDH / HEIGHT), 0.1f, 100.0f);
        // ShaderManager::Instance().SetMat4(program_, "projection", projection);

        glm::vec3 cubePositions[] = {
            glm::vec3( 0.0f,  0.0f,  0.0f),
            glm::vec3( 2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3( 2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3( 1.3f, -2.0f, -2.5f),
            glm::vec3( 1.5f,  2.0f, -2.5f),
            glm::vec3( 1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
        };

        for (int i = 0; i < 10; i++)
        {
            glm::mat4 model = GetModelWithIndex(i, glm::translate(glm::mat4(1.0f), cubePositions[i]));
            ShaderManager::Instance().SetMat4(program_, "model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
    }
}

glm::mat4 SpaceDrawerCube::GetModelWithTime(glm::mat4 model)
{
    return glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
}

glm::mat4 SpaceDrawerCube::GetModelWithIndex(int index, glm::mat4 model)
{
    float radians = 0.0f;
    if (index % 3 == 0)
        radians = (float)glfwGetTime() * glm::radians(20.0f * index);
    return glm::rotate(model, radians, glm::vec3(1.0f, 0.3f, 0.5f));
}

glm::mat4 SpaceDrawerCube::GetViewStatic()
{
    return glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
}

glm::mat4 SpaceDrawerCube::GetViewWithTime()
{
    // glm::vec3 camera_pos = glm::vec3(0.0f, 0.0f, 3.0f);
    // glm::vec3 camera_target = glm::vec3(0.0f);
    // glm::vec3 camera_direction = glm::normalize(camera_pos - camera_target);
    // glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    // glm::vec3 camera_right = glm::normalize(glm::cross(up, camera_direction));
    // glm::vec3 camera_up = glm::cross(camera_direction, camera_right);
    // return glm::lookAt(camera_pos, camera_target, up);

    float radius = 10.0f;
    float cam_x = sin(glfwGetTime()) * radius;
    float cam_y = cos(glfwGetTime()) * radius;
    return glm::lookAt(glm::vec3(cam_x, 0.0, cam_y), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}
