#include "ui/public/colorui.h"

#include "scene/public/sceneheader.h"

void ColorUI::Render()
{
    ImGui::Begin("Scene Color");

    SceneColor* currentScene = dynamic_cast<SceneColor*>(SceneManager::Instance().GetCurrentScene());
    glm::vec4 color = currentScene->cleanColor();
    ImVec4 uicolor = ImVec4(color.r, color.g, color.b, color.a);
    ImGui::ColorEdit4("ClearColor", (float*)&uicolor);



    const char* items[] = { "Fill", "Line" };
    static int item_current = 0;
    ImGui::Combo("combo", &item_current, items, IM_ARRAYSIZE(items));

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();

    currentScene->cleanColor(uicolor.x, uicolor.y, uicolor.z, uicolor.w);
}
