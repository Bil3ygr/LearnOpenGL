#include "mainwindow.h"

#include "utils/helper.h"
#include "scene/sceneheader.h"
#include "control/keyboardmanager.h"
#include "utils/timemanager.h"
#include "ui/uimanager.h"

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

MainWindow::MainWindow()
{
    window_ = nullptr;
    initial_ = false;
    success_ = false;
    last_time_ = 0.0f;
}

MainWindow::~MainWindow()
{
    glfwTerminate();
    window_ = nullptr;
}

void MainWindow::Init(Game* game)
{
    if (initial_)
        return;

    initial_ = true;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window_ = glfwCreateWindow(WITDH, HEIGHT, PROJECT_NAME, NULL, NULL);
    if (!window_)
    {
        ERROR("Failed to create GLFW window\n");
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window_);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        ERROR("Failed to initialize GLAD\n");
        glfwTerminate();
        return;
    }

    glViewport(0, 0, WITDH, HEIGHT);
    glfwSetFramebufferSizeCallback(window_, FramebufferSizeCallback);

    success_ = true;
    game_ = game;
}

void MainWindow::Run()
{
    if (!success_)
        return;

    game_->Init();

    while (Alive())
        Loop();
}

void MainWindow::Loop()
{
    if (!success_ || !window_)
        return;

    float current_time = glfwGetTime();
    TimeManager::Instance().deltaTime(current_time - last_time_);
    last_time_ = current_time;

    KeyboardManager::Instance().ProcessKeyEvent(window_);

    game_->GameLoop();

    SceneManager::Instance().RenderScene();

    UIManager::Instance().Render();

    glfwSwapBuffers(window_);
    glfwPollEvents();
}

void MainWindow::Close()
{
    glfwSetWindowShouldClose(window_, true);
}

bool MainWindow::Alive()
{
    if (!success_ || !window_)
        return false;

    if (glfwWindowShouldClose(window_))
    {
        glfwTerminate();
        window_ = nullptr;
        return false;
    }
    return true;
}
