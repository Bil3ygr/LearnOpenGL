#include "mainwindow.h"

#include "iostream"

#include "utils/helper.h"
#include "scene/sceneheader.h"
#include "control/keyboardmanager.h"
#include "utils/timemanager.h"
#include "ui/uimanager.h"

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void ErrorHandleCallback(int error_code, const char* description)
{
	std::cout <<  "OpenGL error: " << description << std::endl;
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

bool MainWindow::Init(Game* game)
{
    if (initial_)
    {
        return false;
    }

    initial_ = true;

	glfwSetErrorCallback(ErrorHandleCallback);

    if (!glfwInit())
    {
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAJOR_VERSION);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MINOR_VERSION);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window_ = glfwCreateWindow(WITDH, HEIGHT, PROJECT_NAME, NULL, NULL);
    if (!window_)
    {
        ERROR("Failed to create GLFW window\n");
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window_);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        ERROR("Failed to initialize GLAD\n");
        glfwTerminate();
        return false;
    }

    glViewport(0, 0, WITDH, HEIGHT);
    glfwSetFramebufferSizeCallback(window_, FramebufferSizeCallback);

    success_ = true;
    game_ = game;

    return true;
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
