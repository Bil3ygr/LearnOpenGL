#include "globalui.h"

#include "mainwindow.h"
#include "game.h"
#include "scenetriangle.h"
#include "scenewithui.h"
#include "scene/scenemanager.h"

void GlobalUI::Render()
{
    ImGui::SetNextWindowSize(ImVec2(300, 200), ImGuiCond_FirstUseEver);
    ImGui::Begin("Menu", NULL, ImGuiWindowFlags_MenuBar);

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Quit", "Alt+F4"))
                MainWindow::Instance().Close();
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Scene"))
        {
            if (ImGui::MenuItem("Triangle & Rect"))
            {
                auto scene = dynamic_cast<SceneTriangle*>(SceneManager::Instance().GetCurrentScene());
                if (!scene)
                    SceneManager::Instance().SwitchScene(new SceneTriangle());
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    auto current_scene = dynamic_cast<SceneWithUI*>(SceneManager::Instance().GetCurrentScene());
    if (current_scene)
    {
        current_scene->RenderUI();

        glm::vec4 color = current_scene->cleanColor();
        ImVec4 clean_color = ImVec4(color.r, color.g, color.b, color.a);
        ImGui::ColorEdit4("ClearColor", (float*)&clean_color);
        current_scene->cleanColor(clean_color.x, clean_color.y, clean_color.z, clean_color.w);
    }

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
}
