#include "drawer/public/rectdrawer.h"

#include "utils/public/helper.h"

void RectDrawer::Init()
{
    SetShader("shader\\triangle_vs.glsl", "shader\\triangle_fs.glsl");

    float vertices[] = {
        1.0f, 0.0f, 0.0f,   // 右上角
        1.0f, -1.0f, 0.0f,  // 右下角
        0.0f, -1.0f, 0.0f, // 左下角
        0.0f, 0.0f, 0.0f   // 左上角
    };
    int pointers[] = { 3 };
    int indices[] = {
       0, 3, 1,
       3, 2, 1,
    };
    vao_ = DrawerHelper::GetVertexArrayObject(
        vertices, sizeof(vertices),
        pointers, sizeof(pointers) / sizeof(pointers[0]),
        indices, sizeof(indices)
    );
    //SetCleanColor(0.3f, 0.4f, 0.4f);
}

void RectDrawer::_Render()
{
    glUseProgram(program_);
    glBindVertexArray(vao_);
    if (is_line_)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
