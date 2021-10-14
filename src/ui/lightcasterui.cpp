#include "ui/lightcasterui.h"

#include "glm/gtc/type_ptr.hpp"

#include "scene/sceneheader.h"
#include "camera/cameramanager.h"

void LightcasterUI::Render()
{
    ImGui::Begin("Scene Lightcaster");

    SceneLightcaster* currentScene = dynamic_cast<SceneLightcaster*>(SceneManager::Instance().GetCurrentScene());
    glm::vec4 color = currentScene->cleanColor();
    ImVec4 uicolor = ImVec4(color.r, color.g, color.b, color.a);
    ImGui::ColorEdit4("ClearColor", (float*)&uicolor);

    glm::vec3 ambient = currentScene->GetLightAmbient();
    float ui_ambient[3] = { ambient.x, ambient.y, ambient.z };
    ImGui::SliderFloat3("Ambient", ui_ambient, 0.0f, 1.0f);
    glm::vec3 diffuse = currentScene->GetLightDiffuse();
    float ui_diffuse[3] = { diffuse.x, diffuse.y, diffuse.z };
    ImGui::SliderFloat3("Diffuse", ui_diffuse, 0.0f, 1.0f);
    glm::vec3 specular = currentScene->GetLightSpecular();
    float ui_specular[3] = { specular.x, specular.y, specular.z };
    ImGui::SliderFloat3("Specular", ui_specular, 0.0f, 1.0f);

    ImGui::Text("Directional Light");
    glm::vec3 dir_light_dir = currentScene->GetDirLightDirection();
    float ui_dir_light_dir[3] = { dir_light_dir.x, dir_light_dir.y, dir_light_dir.z };
    ImGui::SliderFloat3("DirLight Direction", ui_dir_light_dir, -1.0f, 1.0f);

    ImGui::Text("Point Light");
    glm::vec3 point_light_pos = currentScene->GetPointLightPosition();
    float ui_point_light_pos[3] = { point_light_pos.x, point_light_pos.y, point_light_pos.z };
    ImGui::SliderFloat3("PointLight Position", ui_point_light_pos, -10.0f, 10.0f);
    float constant = currentScene->GetPointLightConstant();
    ImGui::SliderFloat("PointLight Constant", &constant, 0.0f, 1.0f);
    float linear = currentScene->GetPointLightLinear();
    ImGui::SliderFloat("PointLight Linear", &linear, 0.0f, 90.0f);
    float quadratic = currentScene->GetPointLightQuadratic();
    ImGui::SliderFloat("PointLight Quadratic", &quadratic, 0.0f, 90.0f);

    ImGui::Text("Spot Light");
    // glm::vec3 spot_light_pos = currentScene->GetSpotLightPosition();
    // float ui_spot_light_pos[3] = { spot_light_pos.x, spot_light_pos.y, spot_light_pos.z };
    // ImGui::SliderFloat3("SpotLight Position", ui_spot_light_pos, -10.0f, 10.0f);
    // glm::vec3 spot_light_dir = currentScene->GetSpotLightDirection();
    // float ui_spot_light_dir[3] = { spot_light_dir.x, spot_light_dir.y, spot_light_dir.z };
    // ImGui::SliderFloat3("SpotLight Direction", ui_spot_light_dir, -1.0f, 1.0f);
    float cutoff = currentScene->GetSpotLightCutoff();
    ImGui::SliderFloat("SpotLight Cutoff", &cutoff, 0.0f, 90.0f);
    float outter_cutoff = currentScene->GetSpotLightOutterCutoff();
    if (cutoff > outter_cutoff)
        outter_cutoff = cutoff;
    ImGui::SliderFloat("SpotLight OutterCutoff", &outter_cutoff, cutoff, 90.0f);

    SCamera cam = CameraManager::Instance().GetDefaultCamera();
    glm::vec3 pos = cam->pos();
    ImGui::Text("Current camera pos: (%.2f, %.2f, %.2f), fov: %.2f", pos.x, pos.y, pos.z, cam->fov());

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();

    currentScene->cleanColor(uicolor.x, uicolor.y, uicolor.z, uicolor.w);
    currentScene->SetLightAmbient(glm::vec3(ui_ambient[0], ui_ambient[1], ui_ambient[2]));
    currentScene->SetLightDiffuse(glm::vec3(ui_diffuse[0], ui_diffuse[1], ui_diffuse[2]));
    currentScene->SetLightSpecular(glm::vec3(ui_specular[0], ui_specular[1], ui_specular[2]));

    currentScene->SetDirLightDirection(glm::vec3(ui_dir_light_dir[0], ui_dir_light_dir[1], ui_dir_light_dir[2]));

    currentScene->SetPointLightPosition(glm::vec3(ui_point_light_pos[0], ui_point_light_pos[1], ui_point_light_pos[2]));
    currentScene->SetPointLightConstant(constant);
    currentScene->SetPointLightLinear(linear);
    currentScene->SetPointLightQuadratic(quadratic);

    // currentScene->SetSpotLightPosition(glm::vec3(ui_spot_light_pos[0], ui_spot_light_pos[1], ui_spot_light_pos[2]));
    // currentScene->SetSpotLightDirection(glm::vec3(ui_spot_light_dir[0], ui_spot_light_dir[1], ui_spot_light_dir[2]));
    currentScene->SetSpotLightCutoff(cutoff);
    currentScene->SetSpotLightOutterCutoff(outter_cutoff);
}
