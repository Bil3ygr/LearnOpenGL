#include "drawer/public/drawerhelper.h"

GLuint DrawerHelper::GetVertexArrayObject(float* vertices, int vertice_size, int* pointers, int pointer_count)
{
    return GetVertexArrayObject(vertices, vertice_size, pointers, pointer_count, nullptr, nullptr, 0);
}

GLuint DrawerHelper::GetVertexArrayObject(float* vertices, int vertice_size, int* pointers, int pointer_count, bool* enable_pointers)
{
    return GetVertexArrayObject(vertices, vertice_size, pointers, pointer_count, enable_pointers, nullptr, 0);
}

GLuint DrawerHelper::GetVertexArrayObject(float* vertices, int vertice_size, int* pointers, int pointer_count, int* indices, int indice_size)
{
    return GetVertexArrayObject(vertices, vertice_size, pointers, pointer_count, nullptr, indices, indice_size);
}

GLuint DrawerHelper::GetVertexArrayObject(float* vertices, int vertice_size, int* pointers, int pointer_count, bool* enable_pointers, int* indices, int indice_size)
{
    GLuint vao, vbo, ibo = 0;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertice_size, vertices, GL_STATIC_DRAW);

    if (indices)
    {
        glGenBuffers(1, &ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indice_size, indices, GL_STATIC_DRAW);
    }

    int total = 0;
    for (int i = 0; i < pointer_count; ++i)
        total += pointers[i];
    int offset = 0;
    for (int i = 0; i < pointer_count; ++i)
    {
        if (!enable_pointers || enable_pointers[i])
        {
            glVertexAttribPointer(i, pointers[i], GL_FLOAT, GL_FALSE, total * sizeof(float), (void*)(offset * sizeof(float)));
            glEnableVertexAttribArray(i);
        }
        offset += pointers[i];
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glDeleteBuffers(1, &vbo);
    if (indices)
        glDeleteBuffers(1, &ibo);
    return vao;
}
