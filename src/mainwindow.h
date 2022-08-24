#pragma once

#ifndef SRC_MAINWINDOW_H_
#define SRC_MAINWINDOW_H_

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "utils/consts.h"
#include "utils/singleton.h"
#include "game/game.h"

void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

class MainWindow : public Singleton<MainWindow>
{
    friend class Singleton<MainWindow>;
private:
    MainWindow();
    ~MainWindow();

public:
    bool Init(Game* game);
    bool IsSuccess() { return success_; }

    void Run();
    void Loop();

    void Close();
    const GLFWwindow* window() { return window_; }

private:
    bool Alive();

    Game* game_;
    GLFWwindow* window_;
    bool initial_;
    bool success_;
    float last_time_;
};

#endif // !SRC_MAINWINDOW_H_
