#pragma once

#ifndef SRC_MAINWINDOW_H_
#define SRC_MAINWINDOW_H_

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "utils/public/consts.h"
#include "utils/public/singleton.h"

void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

class MainWindow : public Singleton<MainWindow>
{
    friend class Singleton<MainWindow>;
private:
    MainWindow();
    ~MainWindow();

public:
    void Init();
    bool IsSuccess() { return success_; }

    void Loop();

    void Close();
    bool Alive();
    const GLFWwindow* window() { return window_; }

private:
    GLFWwindow* window_;
    bool initial_;
    bool success_;
    float last_time_;
};

#endif // !SRC_MAINWINDOW_H_
