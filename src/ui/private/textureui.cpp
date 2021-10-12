#include "ui/public/textureui.h"

#include "glm/gtc/type_ptr.hpp"

#include "scene/public/sceneheader.h"

void TextureUI::Render()
{
    ImGui::Begin("Texture Scene");

    SceneTexture* currentScene = static_cast<SceneTexture*>(SceneManager::Instance().GetCurrentScene());
    glm::vec4 color = currentScene->cleanColor();
    ImVec4 ui_color = ImVec4(color.r, color.g, color.b, color.a);
    ImGui::ColorEdit4("Clear color", (float*)&ui_color);

    ImGui::Text("LeftTop");
    bool rotate = currentScene->autoRotate();
    ImGui::Checkbox("Auto rotate", &rotate);
    float speed = currentScene->rotateSpeed();
    ImGui::SliderFloat("Rotate speed", &speed, 0.0f, 10.0f);
    float degree = currentScene->rotateRadian();
    ImGui::SliderAngle("Rotate degree", &degree);

    ImGui::Text("RightTop");
    float mix_value = currentScene->mixValue();
    ImGui::SliderFloat("Mix value", &mix_value, 0.0f, 1.0f);

    ImGui::Text("LeftBottom");
    glm::vec3 scale = currentScene->scale();
    float ui_scale[3] = { scale.x, scale.y, scale.z };
    ImGui::SliderFloat3("Scale", ui_scale, 0.0f, 1.0f);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();

    currentScene->cleanColor(ui_color.x, ui_color.y, ui_color.z, ui_color.w);
    currentScene->autoRotate(rotate);
    currentScene->rotateSpeed(speed);
    currentScene->rotateRadian(degree);
    currentScene->mixValue(mix_value);
    currentScene->scale(glm::vec3(ui_scale[0], ui_scale[1], ui_scale[2]));
}
