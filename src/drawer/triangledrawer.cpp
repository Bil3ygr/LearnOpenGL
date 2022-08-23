#include "drawer/triangledrawer.h"

#include "GLFW/glfw3.h"

#include "render/shadermanager.h"
#include "utils/helper.h"

void TriangleDrawer::Init()
{
    SetShader("shader\\triangle_vs.glsl", "shader\\triangle_fs.glsl");

    float vertices[] = {
        -1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        -0.5f, 1.0f, 0.0f,
    };
    int pointers[] = { 3 };
    vao_ = DrawerHelper::GetVertexArrayObject(
        vertices, sizeof(vertices),
        pointers, sizeof(pointers) / sizeof(pointers[0])
    );
}

void TriangleDrawer::_Render()
{
    glUseProgram(program_);
    glBindVertexArray(vao_);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void TriangleDrawerPractice::Init()
{
    SetShader("shader\\triangle_vs.glsl", "shader\\triangle_practice_fs.glsl");

    float vertices[] = {
        0.0f, 0.0f, 0.0f,
        -0.5f, 1.0f, 0.0f,
        0.5f, 1.0f, 0.0f,
    };
    int pointers[] = { 3 };
    vao_ = DrawerHelper::GetVertexArrayObject(
        vertices, sizeof(vertices),
        pointers, sizeof(pointers) / sizeof(pointers[0])
    );
}

void TriangleDrawerWithTimeColor::Init()
{
    SetShader("shader\\triangle_vs.glsl", "shader\\triangle_time_color_fs.glsl");

    float vertices[] = {
        -1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        -0.5f, 1.0f, 0.0f,
    };
    int pointers[] = { 3 };
    vao_ = DrawerHelper::GetVertexArrayObject(
        vertices, sizeof(vertices),
        pointers, sizeof(pointers) / sizeof(pointers[0])
    );
}

void TriangleDrawerWithTimeColor::_Render()
{
    glUseProgram(program_);
    {
        float green = (sin(glfwGetTime()) / 2.0f) + 0.5f;
        ShaderManager::Instance().SetVec4(program_, "ourColor", 0.0f, green, 0.0f, 1.0f);
    }
    glBindVertexArray(vao_);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void TriangleDrawerWithInitColor::Init()
{
    SetShader("shader\\triangle_init_color_vs.glsl", "shader\\triangle_fs.glsl");

    float vertices[] = {
        0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    };
    int pointers[] = { 3, 3 };
    vao_ = DrawerHelper::GetVertexArrayObject(
        vertices, sizeof(vertices),
        pointers, sizeof(pointers) / sizeof(pointers[0])
    );
}

void TriangleDrawerWithInitColorPractice::Init()
{
    SetShader("shader\\triangle_init_color_practice_vs.glsl", "shader\\triangle_fs.glsl");

    float vertices[] = {
        0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    };
    int pointers[] = { 3, 3 };
    vao_ = DrawerHelper::GetVertexArrayObject(
        vertices, sizeof(vertices),
        pointers, sizeof(pointers) / sizeof(pointers[0])
    );
}

void TriangleDrawerWithInitColorPractice::_Render()
{
    glUseProgram(program_);
    {
        float offset = (sin(glfwGetTime()) / 2.0f) - 0.5f;
        ShaderManager::Instance().SetFloat(program_, "offsetY", offset);
    }
    glBindVertexArray(vao_);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
