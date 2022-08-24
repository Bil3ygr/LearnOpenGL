#pragma once

#ifndef SRC_UTILS_CONSTS_H_
#define SRC_UTILS_CONSTS_H_

#define WITDH 800
#define HEIGHT 800
#define OPENGL_MAJOR_VERSION 4
#if __APPLE__
#define OPENGL_MINOR_VERSION 1
#else
#define OPENGL_MINOR_VERSION 6
#endif
#define PROJECT_NAME "LearnOpenGL"

extern float array_cube_normal[216];
extern float array_cube_texture[180];
extern float array_cube_normal_texture[288];

#endif // !SRC_UTILS_CONSTS_H_
