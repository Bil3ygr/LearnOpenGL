#include "ui/public/defaultui.h"

#include "scene/public/scenemanager.h"

void DefaultUI::Render()
{
    ImGui::Begin("Default Scene");

    Scene* currentScene = SceneManager::Instance().GetCurrentScene();
    glm::vec4 color = currentScene->cleanColor();
    ImVec4 uicolor = ImVec4(color.r, color.g, color.b, color.a);
    ImGui::ColorEdit4("ClearColor", (float*)&uicolor);
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();

    currentScene->cleanColor(uicolor.x, uicolor.y, uicolor.z, uicolor.w);
}
