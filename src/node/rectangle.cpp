#include "rectangle.h"

#include <stdexcept>

#include "glm/gtc/type_ptr.hpp"

#include "drawer/drawerhelper.h"
#include "render/shadermanager.h"
#include "utils/helper.h"

#define LEN_VTX 3
#define LEN_CLR 4
#define LEN_ARRAY 4 * (LEN_VTX + LEN_CLR)

Rectangle::Rectangle(const std::string& name) : BaseNode(name)
{
    program_ = ShaderManager::Instance().GetShaderProgram("shader\\triangle_vs.glsl", "shader\\triangle_fs.glsl");
    vao_ = 0;
    update_ = true;
    vertices_ = std::vector<VertexInfo>();
    line_mode_ = false;
}

Rectangle::~Rectangle()
{

}

void Rectangle::Render()
{
    PreRender();

    if (!program_ || !vao_)
        return;

    glUseProgram(program_);
    glBindVertexArray(vao_);
    if (line_mode_)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    ShaderManager::Instance().SetBool(program_, "enable", false);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Rectangle::Clear()
{
    update_ = true;
    vertices_.clear();
}

VertexInfo& Rectangle::operator[](const int& idx)
{
    int size = vertices_.size();
    if (idx > size)
        throw std::out_of_range("rectangle index out of range");
    else if (idx == size)
        vertices_.emplace_back(VertexInfo());
    return vertices_[idx];
}

void Rectangle::PreRender()
{
    if (update_)
    {
        float* data = new float[LEN_ARRAY];
        for (int i = 0; i < LEN_ARRAY; i++)
        {
            int remainder = i % (LEN_VTX + LEN_CLR);
            if (remainder < LEN_VTX)
                data[i] = vertices_[i / (LEN_VTX + LEN_CLR)].vertex[remainder];
            else
                data[i] = vertices_[i / (LEN_VTX + LEN_CLR)].color[remainder - LEN_VTX];
        }
        int pointers[] = { LEN_VTX, LEN_CLR };
        int indices[] = {
            0, 1, 2,
            0, 2, 3,
        };
        vao_ = DrawerHelper::GetVertexArrayObject(data, sizeof(float) * LEN_ARRAY, pointers, 2, indices, sizeof(indices));
        delete[] data;
    }
}
