#include "triangle.h"

#include <stdexcept>

#include "glm/gtc/type_ptr.hpp"

#include "drawer/drawerhelper.h"
#include "render/shadermanager.h"
#include "utils/helper.h"

#define POINT_COUNT 3
#define LEN_VTX 3
#define LEN_CLR 4
#define LEN_ARRAY 3 * (LEN_VTX + LEN_CLR)

Triangle::Triangle(const std::string& name) : BaseNode(name)
{
    program_ = ShaderManager::Instance().GetShaderProgram("shader\\triangle_vs.glsl", "shader\\triangle_fs.glsl");
    vao_ = 0;
    update_ = true;
    vertices_ = std::vector<VertexInfo>();
}

Triangle::~Triangle()
{

}

void Triangle::Render()
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

void Triangle::Clear()
{
    update_ = true;
    vertices_.clear();
}

VertexInfo& Triangle::operator[](const int& idx)
{
    int size = vertices_.size();
    if (idx > size)
        throw std::out_of_range("triangle index out of range");
    else if (idx == size)
        vertices_.emplace_back(VertexInfo());
    return vertices_[idx];
}

void Triangle::PreRender()
{
    if (update_)
    {
        if (vao_)
            glDeleteVertexArrays(1, &vao_);

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
        vao_ = DrawerHelper::GetVertexArrayObject(data, sizeof(float) * LEN_ARRAY, pointers, 2);
        delete[] data;
        update_ = false;
    }
}
