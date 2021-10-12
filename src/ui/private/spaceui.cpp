#include "ui/public/spaceui.h"

#include "scene/public/sceneheader.h"
#include "camera/public/cameramanager.h"

void SpaceUI::Render()
{
    ImGui::Begin("Scene Space");

    SceneSpace* currentScene = dynamic_cast<SceneSpace*>(SceneManager::Instance().GetCurrentScene());
    glm::vec4 color = currentScene->cleanColor();
    ImVec4 uicolor = ImVec4(color.r, color.g, color.b, color.a);
    ImGui::ColorEdit4("ClearColor", (float*)&uicolor);

    SCamera cam = CameraManager::Instance().GetDefaultCamera();
    glm::vec3 pos = cam->pos();
    ImGui::Text("Current camera pos: (%.2f, %.2f, %.2f), fov: %.2f", pos.x, pos.y, pos.z, cam->fov());
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();

    currentScene->cleanColor(uicolor.x, uicolor.y, uicolor.z, uicolor.w);
}
