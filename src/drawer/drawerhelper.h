#pragma once

#ifndef SRC_DRAWER_DRAWERHELPER_H_
#define SRC_DRAWER_DRAWERHELPER_H_

#include "glad/glad.h"

class DrawerHelper
{
public:
    static GLuint GetVertexArrayObject(float* vertices, int vertice_size, int* pointers, int pointer_count);
    static GLuint GetVertexArrayObject(float* vertices, int vertice_size, int* pointers, int pointer_count, bool* enable_pointers);
    static GLuint GetVertexArrayObject(float* vertices, int vertice_size, int* pointers, int pointer_count, int* indices, int indice_size);
    static GLuint GetVertexArrayObject(float* vertices, int vertice_size, int* pointers, int pointer_count, bool* enable_pointers, int* indices, int indice_size);
};

#endif // !SRC_DRAWER_DRAWERHELPER_H_
