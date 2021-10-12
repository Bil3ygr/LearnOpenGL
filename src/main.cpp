#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "mainwindow.h"
#include "scene/public/sceneheader.h"
#include "utils/public/keyboardmanager.h"
#include "utils/public/mousemanager.h"
#include "camera/public/cameramanager.h"

void RegisterScene()
{
    REGISTER_SCENE_CREATOR(SceneType::kDefault, SceneDefault);
    REGISTER_SCENE_CREATOR(SceneType::kTriangle, SceneTriangle);
    REGISTER_SCENE_CREATOR(SceneType::kTexture, SceneTexture);
    REGISTER_SCENE_CREATOR(SceneType::kSpace, SceneSpace);
    REGISTER_SCENE_CREATOR(SceneType::kColor, SceneColor);
    REGISTER_SCENE_CREATOR(SceneType::kLightmap, SceneLightmap);
}

void RegisterKeyboard()
{
    REGISTER_KEYBOARD_PRESS(GLFW_KEY_ESCAPE, "Escape", MainWindow::Instance().Close());
    REGISTER_KEYBOARD_PRESS(GLFW_KEY_0, std::string(SceneTypeToString(SceneType::kDefault)), SWITCH_SCENE(SceneType::kDefault));
    REGISTER_KEYBOARD_PRESS(GLFW_KEY_1, std::string(SceneTypeToString(SceneType::kTriangle)), SWITCH_SCENE(SceneType::kTriangle));
    REGISTER_KEYBOARD_PRESS(GLFW_KEY_2, std::string(SceneTypeToString(SceneType::kTexture)), SWITCH_SCENE(SceneType::kTexture));
    REGISTER_KEYBOARD_PRESS(GLFW_KEY_3, std::string(SceneTypeToString(SceneType::kSpace)), SWITCH_SCENE(SceneType::kSpace));
    REGISTER_KEYBOARD_PRESS(GLFW_KEY_4, std::string(SceneTypeToString(SceneType::kColor)), SWITCH_SCENE(SceneType::kColor));
    REGISTER_KEYBOARD_PRESS(GLFW_KEY_5, std::string(SceneTypeToString(SceneType::kLightmap)), SWITCH_SCENE(SceneType::kLightmap));
}

void InputModeChanged(int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_RIGHT)
    {
        if (action == GLFW_PRESS)
        {
            MouseManager::Instance().moveEnable(true);
            glfwSetInputMode(const_cast<GLFWwindow*>(MainWindow::Instance().window()), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
        else if (action == GLFW_RELEASE)
        {
            MouseManager::Instance().moveEnable(false);
            glfwSetInputMode(const_cast<GLFWwindow*>(MainWindow::Instance().window()), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            CameraManager::Instance().ResetMousePos();
        }
    }
}

void RegisterMouse()
{
    REGISTER_MOUSE_BUTTON("InputMode", InputModeChanged);
    // if (enable)
    //         glfwSetInputMode(const_cast<GLFWwindow*>(MainWindow::Instance().window()), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    //     else
    //         glfwSetInputMode(const_cast<GLFWwindow*>(MainWindow::Instance().window()), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Loop()
{
    while (MainWindow::Instance().Alive())
        MainWindow::Instance().Loop();
}

int main()
{
    MainWindow::Instance().Init();

    RegisterScene();
    RegisterKeyboard();
    RegisterMouse();

    Loop();

    return 0;
}
