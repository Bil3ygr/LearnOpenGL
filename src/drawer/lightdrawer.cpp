#include "drawer/lightdrawer.h"

#include "control/mousemanager.h"
#include "utils/helper.h"

LightDrawer::LightDrawer()
{
    camera_ = CameraManager::Instance().GetDefaultCamera();
    if (!camera_)
        camera_ = CameraManager::Instance().CreateCamera(0);
    point_light_ = nullptr;
    spot_light_ = nullptr;
}

LightDrawer::~LightDrawer()
{
    glDisable(GL_DEPTH_TEST);
    camera_ = nullptr;
    point_light_ = nullptr;
    spot_light_ = nullptr;
}

void LightDrawer::Init()
{
    glEnable(GL_DEPTH_TEST);

    SetShader("shader\\color_vs.glsl", "shader\\color_light_fs.glsl");

    int pointers[] = { 3, 3 };
    bool enable_pointers[] = { true, false };
    vao_ = DrawerHelper::GetVertexArrayObject(
        array_cube_normal, sizeof(array_cube_normal),
        pointers, sizeof(pointers) / sizeof(pointers[0]),
        enable_pointers
    );
}

void LightDrawer::SetPointLight(std::shared_ptr<PointLight> light)
{
    if (spot_light_)
    {
        ERROR("Already set spot light, cannot set point light!\n");
        return;
    }
    point_light_ = light;
}

void LightDrawer::SetSpotLight(std::shared_ptr<SpotLight> light)
{
    if (point_light_)
    {
        ERROR("Already set point light, cannot set spot light!\n");
        return;
    }
    spot_light_ = light;
}

void LightDrawer::_Render()
{
    if (!point_light_ && !spot_light_)
        return;

    glClear(GL_DEPTH_BUFFER_BIT);

    glBindVertexArray(vao_);
    glUseProgram(program_);

    camera_.get()->SetProgram(program_);
    camera_.get()->Update();

    // practice, rotate with time
    glm::mat4 light_model(1.0f);
    if (point_light_)
        light_model = glm::translate(light_model, glm::vec3(point_light_.get()->position()));
    else if (spot_light_)
        light_model = glm::translate(light_model, glm::vec3(spot_light_.get()->position()));
    light_model = glm::scale(light_model, glm::vec3(0.2f));
    ShaderManager::Instance().SetMat4(program_, "model", light_model);

    glDrawArrays(GL_TRIANGLES, 0, 36);
}
