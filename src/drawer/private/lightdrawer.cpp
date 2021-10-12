#include "drawer/public/lightdrawer.h"

#include "utils/public/mousemanager.h"

LightDrawer::LightDrawer()
{
    camera_ = CameraManager::Instance().GetDefaultCamera();
    if (!camera_)
        camera_ = CameraManager::Instance().CreateCamera(0);
    light_ = nullptr;
}

LightDrawer::~LightDrawer()
{
    glDisable(GL_DEPTH_TEST);
    camera_ = nullptr;
    light_ = nullptr;
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

void LightDrawer::_Render()
{
    if (!light_)
        return;

    // directional light, not draw
    if (light_.get()->vector().w == 0.0f)
        return;

    glClear(GL_DEPTH_BUFFER_BIT);

    glBindVertexArray(vao_);
    glUseProgram(program_);

    camera_.get()->SetProgram(program_);
    camera_.get()->Update();

    // practice, rotate with time
    glm::mat4 light_model(1.0f);
    // glm::mat4 light_model = glm::rotate(glm::mat4(1.0f), (float)glfwGetTime() * glm::radians(60.0f), glm::vec3(0, 1.0f, 0));
    light_model = glm::translate(light_model, glm::vec3(light_.get()->vector()));
    // light_model = glm::translate(light_model, glm::vec3(1.2f, 1.0f, 2.0f));
    light_model = glm::scale(light_model, glm::vec3(0.2f));

    ShaderManager::Instance().SetMat4(program_, "model", light_model);

    glDrawArrays(GL_TRIANGLES, 0, 36);

    // change color with time
    // glm::vec3 color;
    // color.x = sin(glfwGetTime() * 2.0f);
    // color.y = sin(glfwGetTime() * 0.7f);
    // color.z = sin(glfwGetTime() * 1.3f);
    // glm::vec3 diffuse = color * glm::vec3(0.5f);
    // glm::vec3 ambient = diffuse * glm::vec3(0.2f);
    // light_.get()->ambient(ambient);
    // light_.get()->diffuse(diffuse);
}
