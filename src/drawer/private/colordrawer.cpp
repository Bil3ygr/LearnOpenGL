#include "drawer/public/colordrawer.h"

#include "utils/public/consts.h"
#include "utils/public/mousemanager.h"
#include "utils/public/shadermanager.h"

ColorDrawer::ColorDrawer() : BaseDrawer()
{
    camera_ = CameraManager::Instance().GetDefaultCamera();
    if (!camera_)
        camera_ = CameraManager::Instance().CreateCamera(0);
    light_ = nullptr;
    MouseManager::Instance().buttonEnable(true);
}

ColorDrawer::~ColorDrawer()
{
    glDisable(GL_DEPTH_TEST);
    camera_ = nullptr;
    light_ = nullptr;
    MouseManager::Instance().buttonEnable(false);
}

void ColorDrawer::Init()
{
    glEnable(GL_DEPTH_TEST);

    SetShader("shader\\color_vs.glsl", "shader\\color_fs.glsl");

    int pointers[] = { 3, 3 };
    bool pointers_enable[] = { true, false };
    vao_ = DrawerHelper::GetVertexArrayObject(
        array_cube_normal, sizeof(array_cube_normal),
        pointers, sizeof(pointers) / sizeof(pointers[0]),
        pointers_enable
    );
}

void ColorDrawer::_Render()
{
    glClear(GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // draw cube
    {
        glBindVertexArray(vao_);
        glUseProgram(program_);

        camera_.get()->SetProgram(program_);
        camera_.get()->Update();

        ShaderManager::Instance().SetVec3(program_, "objectColor", glm::vec3(1.0f));
        ShaderManager::Instance().SetVec3(program_, "lightColor", glm::vec3(1.0f, 0.5f, 0.31f));
        ShaderManager::Instance().SetMat4(program_, "model", glm::mat4(1.0f));
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

void ColorLightingDrawer::Init()
{
    glEnable(GL_DEPTH_TEST);

    SetShader("shader\\color_lighting_vs.glsl", "shader\\color_lighting_fs.glsl");

    int pointers[] = { 3, 3 };
    vao_ = DrawerHelper::GetVertexArrayObject(
        array_cube_normal, sizeof(array_cube_normal),
        pointers, sizeof(pointers) / sizeof(pointers[0])
    );
    // SetCleanColor(0.1f, 0.1f, 0.1f);
}

void ColorLightingDrawer::_Render()
{
    glClear(GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glBindVertexArray(vao_);
    glUseProgram(program_);
    camera_.get()->SetProgram(program_);
    camera_.get()->Update();
    // draw diffuse cube
    {
        ShaderManager::Instance().SetVec3(program_, "objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
        ShaderManager::Instance().SetVec3(program_, "lightColor", glm::vec3(1.0f));
        ShaderManager::Instance().SetVec3(program_, "lightPos", glm::vec3(light_.get()->vector()));
        ShaderManager::Instance().SetMat4(program_, "model", glm::mat4(1.0f));
        ShaderManager::Instance().SetFloat(program_, "specularStrength", 0);

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    // draw specular cube
    {
        ShaderManager::Instance().SetVec3(program_, "objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
        ShaderManager::Instance().SetVec3(program_, "lightColor", glm::vec3(1.0f));
        ShaderManager::Instance().SetVec3(program_, "lightPos", glm::vec3(light_.get()->vector()));
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(2.4f, 0.0f, 0.0f));
        ShaderManager::Instance().SetMat4(program_, "model", model);
        ShaderManager::Instance().SetVec3(program_, "viewPos", camera_.get()->pos());
        ShaderManager::Instance().SetFloat(program_, "specularStrength", 0.5f);

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

void ColorMaterialDrawer::Init()
{
    glEnable(GL_DEPTH_TEST);

    SetShader("shader\\color_lighting_vs.glsl", "shader\\color_material_fs.glsl");

    int pointers[] = { 3, 3 };
    vao_ = DrawerHelper::GetVertexArrayObject(
        array_cube_normal, sizeof(array_cube_normal),
        pointers, sizeof(pointers) / sizeof(pointers[0])
    );
    // SetCleanColor(0.1f, 0.1f, 0.1f);
}

void ColorMaterialDrawer::_Render()
{
    glClear(GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glBindVertexArray(vao_);
    glUseProgram(program_);
    camera_.get()->SetProgram(program_);
    camera_.get()->Update();
    ShaderManager::Instance().SetVec3(program_, "viewPos", camera_.get()->pos());

    ShaderManager::Instance().SetVec3(program_, "light.ambient", light_.get()->ambient());
    ShaderManager::Instance().SetVec3(program_, "light.diffuse", light_.get()->diffuse());
    ShaderManager::Instance().SetVec3(program_, "light.specular", light_.get()->specular());
    ShaderManager::Instance().SetVec4(program_, "light.vector", light_.get()->vector());
    // draw sliver cube
    {
        // ShaderManager::Instance().SetVec3(program_, "material.ambient", 0.19225f, 0.19225f, 0.19225f);
        // ShaderManager::Instance().SetVec3(program_, "material.diffuse", 0.50754f, 0.50754f, 0.50754f);
        // ShaderManager::Instance().SetVec3(program_, "material.specular", 0.508273f, 0.508273f, 0.508273f);
        // ShaderManager::Instance().SetFloat(program_, "material.shininess", 0.4f);
        ShaderManager::Instance().SetVec3(program_, "material.ambient", 1.0f, 0.5f, 0.31f);
        ShaderManager::Instance().SetVec3(program_, "material.diffuse", 1.0f, 0.5f, 0.31f);
        ShaderManager::Instance().SetVec3(program_, "material.specular", glm::vec3(0.5f));
        ShaderManager::Instance().SetFloat(program_, "material.shininess", 32.0f);

        // ShaderManager::Instance().SetVec3(program_, "lightColor", glm::vec3(1.0f));
        ShaderManager::Instance().SetMat4(program_, "model", glm::mat4(1.0f));

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    // draw gold cube
    {
        ShaderManager::Instance().SetVec3(program_, "material.ambient", 0.24725f, 0.1995f, 0.0745f);
        ShaderManager::Instance().SetVec3(program_, "material.diffuse", 0.75164f, 0.60648f, 0.22648f);
        ShaderManager::Instance().SetVec3(program_, "material.specular", 0.628281f, 0.555802f, 0.366065f);
        ShaderManager::Instance().SetFloat(program_, "material.shininess", 0.4f * 128);

        // ShaderManager::Instance().SetVec3(program_, "lightColor", glm::vec3(1.0f));
        // ShaderManager::Instance().SetVec3(program_, "lightPos", glm::vec3(light_.get()->vector()));
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(2.4f, 0.0f, 0.0f));
        ShaderManager::Instance().SetMat4(program_, "model", model);

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

ColorMaterialTableDrawer::ColorMaterialTableDrawer() : ColorDrawer()
{
    materials_ = std::vector<MaterialData>();
    materials_.emplace_back(MaterialData("emerald", glm::vec3(0.0215f, 0.1745f, 0.0215f), glm::vec3(0.07568f, 0.61424f, 0.07568f), glm::vec3(0.633f, 0.727811f, 0.633f)));
    materials_.emplace_back(MaterialData("jade", glm::vec3(0.135f, 0.2225f, 0.1575f), glm::vec3(0.54f, 0.89f, 0.63f), glm::vec3(0.316228f, 0.316228f, 0.316228f)));
    materials_.emplace_back(MaterialData("obsidian", glm::vec3(0.05375f, 0.05f, 0.06625f), glm::vec3(0.18275f, 0.17f, 0.22525f), glm::vec3(0.332741f, 0.328634f, 0.346435f)));
    materials_.emplace_back(MaterialData("pearl", glm::vec3(0.25f, 0.20725f, 0.20725f), glm::vec3(1.0f, 0.829f, 0.829f), glm::vec3(0.296648f, 0.296648f, 0.296648f)));
    materials_.emplace_back(MaterialData("ruby", glm::vec3(0.1745f, 0.01175f, 0.01175f), glm::vec3(0.61424f, 0.04136f, 0.04136f), glm::vec3(0.727811f, 0.626959f, 0.626959f)));
    materials_.emplace_back(MaterialData("turquoise", glm::vec3(0.1f, 0.18725f, 0.1745f), glm::vec3(0.396f, 0.74151f, 0.69102f), glm::vec3(0.297254f, 0.30829f, 0.306678f)));
    materials_.emplace_back(MaterialData("brass", glm::vec3(0.329412f, 0.223529f, 0.027451f), glm::vec3(0.780392f, 0.568627f, 0.113725f), glm::vec3(0.992157f, 0.941176f, 0.807843f)));
    materials_.emplace_back(MaterialData("bronze", glm::vec3(0.2125f, 0.1275f, 0.054f), glm::vec3(0.714f, 0.4284f, 0.18144f), glm::vec3(0.393548f, 0.271906f, 0.166721f)));
    materials_.emplace_back(MaterialData("chrome", glm::vec3(0.25f, 0.25f, 0.25f), glm::vec3(0.4f, 0.4f, 0.4f), glm::vec3(0.774597f, 0.774597f, 0.774597f)));
    materials_.emplace_back(MaterialData("copper", glm::vec3(0.19125f, 0.0735f, 0.0225f), glm::vec3(0.7038f, 0.27048f, 0.0828f), glm::vec3(0.256777f, 0.137622f, 0.086014f)));
    materials_.emplace_back(MaterialData("gold", glm::vec3(0.24725f, 0.1995f, 0.0745f), glm::vec3(0.75164f, 0.60648f, 0.22648f), glm::vec3(0.628281f, 0.555802f, 0.366065f)));
    materials_.emplace_back(MaterialData("silver", glm::vec3(0.19225f, 0.19225f, 0.19225f), glm::vec3(0.50754f, 0.50754f, 0.50754f), glm::vec3(0.508273f, 0.508273f, 0.508273f)));
    materials_.emplace_back(MaterialData("black_plastic", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.01f, 0.01f, 0.01f), glm::vec3(0.50f, 0.50f, 0.50f)));
    materials_.emplace_back(MaterialData("cyan_plastic", glm::vec3(0.0f, 0.1f, 0.06f), glm::vec3(0.0f, 0.50980392f, 0.50980392f), glm::vec3(0.50196078f, 0.50196078f, 0.50196078f)));
    materials_.emplace_back(MaterialData("green_plastic", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.1f, 0.35f, 0.1f), glm::vec3(0.45f, 0.55f, 0.45f)));
    materials_.emplace_back(MaterialData("red_plastic", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.0f, 0.0f), glm::vec3(0.7f, 0.6f, 0.6f)));
    materials_.emplace_back(MaterialData("white_plastic", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.55f, 0.55f, 0.55f), glm::vec3(0.70f, 0.70f, 0.70f)));
    materials_.emplace_back(MaterialData("yellow_plastic", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0.60f, 0.60f, 0.50f)));
    materials_.emplace_back(MaterialData("black_rubber", glm::vec3(0.02f, 0.02f, 0.02f), glm::vec3(0.01f, 0.01f, 0.01f), glm::vec3(0.4f, 0.4f, 0.4f)));
    materials_.emplace_back(MaterialData("cyan_rubber", glm::vec3(0.0f, 0.05f, 0.05f), glm::vec3(0.4f, 0.5f, 0.5f), glm::vec3(0.04f, 0.7f, 0.7f)));
    materials_.emplace_back(MaterialData("green_rubber", glm::vec3(0.0f, 0.05f, 0.0f), glm::vec3(0.4f, 0.5f, 0.4f), glm::vec3(0.04f, 0.7f, 0.04f)));
    materials_.emplace_back(MaterialData("red_rubber", glm::vec3(0.05f, 0.0f, 0.0f), glm::vec3(0.5f, 0.4f, 0.4f), glm::vec3(0.7f, 0.04f, 0.04f)));
    materials_.emplace_back(MaterialData("white_rubber", glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.7f, 0.7f, 0.7f)));
    materials_.emplace_back(MaterialData("yellow_rubber", glm::vec3(0.05f, 0.05f, 0.0f), glm::vec3(0.5f, 0.5f, 0.4f), glm::vec3(0.7f, 0.7f, 0.04f)));
}

ColorMaterialTableDrawer::~ColorMaterialTableDrawer()
{
    materials_.clear();
}

void ColorMaterialTableDrawer::Init()
{
    glEnable(GL_DEPTH_TEST);

    SetShader("shader\\color_lighting_vs.glsl", "shader\\color_material_fs.glsl");

    int pointers[] = { 3, 3 };
    vao_ = DrawerHelper::GetVertexArrayObject(
        array_cube_normal, sizeof(array_cube_normal),
        pointers, sizeof(pointers) / sizeof(pointers[0])
    );
    // SetCleanColor(0.1f, 0.1f, 0.1f);
}

void ColorMaterialTableDrawer::_Render()
{
    glClear(GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glBindVertexArray(vao_);
    glUseProgram(program_);
    camera_.get()->SetProgram(program_);
    camera_.get()->Update();
    ShaderManager::Instance().SetVec3(program_, "viewPos", camera_.get()->pos());

    ShaderManager::Instance().SetVec3(program_, "light.ambient", light_.get()->ambient());
    ShaderManager::Instance().SetVec3(program_, "light.diffuse", light_.get()->diffuse());
    ShaderManager::Instance().SetVec3(program_, "light.specular", light_.get()->specular());
    ShaderManager::Instance().SetVec4(program_, "light.vector", light_.get()->vector());

    for (int i = 0; i < materials_.size(); i++)
    {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3((i % 6) * 2.0f, (i / 6) * 2.0f, 0.0f));
        ShaderManager::Instance().SetMat4(program_, "model", model);

        ShaderManager::Instance().SetVec3(program_, "material.ambient", materials_[i].ambient);
        ShaderManager::Instance().SetVec3(program_, "material.diffuse", materials_[i].diffuse);
        ShaderManager::Instance().SetVec3(program_, "material.specular", materials_[i].specular);
        ShaderManager::Instance().SetFloat(program_, "material.shininess", 1.0f);

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}
