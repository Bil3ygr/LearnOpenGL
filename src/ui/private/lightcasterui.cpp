#include "ui/public/lightcasterui.h"

#include "glm/gtc/type_ptr.hpp"

#include "scene/public/sceneheader.h"
#include "camera/public/cameramanager.h"

void LightcasterUI::Render()
{
    ImGui::Begin("Scene Lightcaster");

    SceneLightcaster* currentScene = dynamic_cast<SceneLightcaster*>(SceneManager::Instance().GetCurrentScene());
    glm::vec4 color = currentScene->cleanColor();
    ImVec4 uicolor = ImVec4(color.r, color.g, color.b, color.a);
    ImGui::ColorEdit4("ClearColor", (float*)&uicolor);

    ImGui::Text("Directional/Point Light");
    glm::vec3 ambient = currentScene->GetLightAmbient();
    float ui_ambient[3] = { ambient.x, ambient.y, ambient.z };
    ImGui::SliderFloat3("Ambient", ui_ambient, 0.0f, 1.0f);

    glm::vec3 diffuse = currentScene->GetLightDiffuse();
    float ui_diffuse[3] = { diffuse.x, diffuse.y, diffuse.z };
    ImGui::SliderFloat3("Diffuse", ui_diffuse, 0.0f, 1.0f);

    glm::vec3 specular = currentScene->GetLightSpecular();
    float ui_specular[3] = { specular.x, specular.y, specular.z };
    ImGui::SliderFloat3("Specular", ui_specular, 0.0f, 1.0f);

    bool is_point = currentScene->IsPointLight();
    ImGui::Checkbox("IsPointLight", &is_point);

    glm::vec3 vector3 = currentScene->GetLightVector3();
    float ui_vector3[3] = { vector3.x, vector3.y, vector3.z };
    ImGui::SliderFloat3("Vector", ui_vector3, -5.0f, 5.0f);

    ImGui::Text("Spot Light");
    float cutoff = currentScene->GetSpotLightCutoff();
    ImGui::SliderFloat("Cutoff", &cutoff, 0.0f, 90.0f);

    float outter_cutoff = currentScene->GetSpotLightOutterCutoff();
    ImGui::SliderFloat("Outter Cutoff", &outter_cutoff, 0.0f, 90.0f);

    SCamera cam = CameraManager::Instance().GetDefaultCamera();
    glm::vec3 pos = cam->pos();
    ImGui::Text("Current camera pos: (%.2f, %.2f, %.2f), fov: %.2f", pos.x, pos.y, pos.z, cam->fov());

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();

    currentScene->cleanColor(uicolor.x, uicolor.y, uicolor.z, uicolor.w);
    currentScene->SetLightAmbient(glm::vec3(ui_ambient[0], ui_ambient[1], ui_ambient[2]));
    currentScene->SetLightDiffuse(glm::vec3(ui_diffuse[0], ui_diffuse[1], ui_diffuse[2]));
    currentScene->SetLightSpecular(glm::vec3(ui_specular[0], ui_specular[1], ui_specular[2]));
    currentScene->SetLightVector3(glm::vec3(ui_vector3[0], ui_vector3[1], ui_vector3[2]));
    currentScene->SetIsPointLight(is_point);
    currentScene->SetSpotLightCutoff(cutoff);
    currentScene->SetSpotLightOutterCutoff(outter_cutoff);
}
