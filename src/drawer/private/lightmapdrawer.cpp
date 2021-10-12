#include "drawer/public/lightmapdrawer.h"

#include "utils/public/consts.h"
#include "utils/public/mousemanager.h"
#include "utils/public/texturemanager.h"

LightmapDrawer::LightmapDrawer()
{
    camera_ = CameraManager::Instance().GetDefaultCamera();
    if (!camera_)
        camera_ = CameraManager::Instance().CreateCamera(0);
    light_ = nullptr;
    texture_ = 0;
    specular_texture_ = 0;
    MouseManager::Instance().buttonEnable(true);
}

LightmapDrawer::~LightmapDrawer()
{
    depth_test(false);
    camera_ = nullptr;
    light_ = nullptr;
    texture_ = 0;
    specular_texture_ = 0;
    MouseManager::Instance().buttonEnable(false);
}

void LightmapDrawer::Init()
{
    depth_test(true);

    SetShader("shader\\lightmap_vs.glsl", "shader\\lightmap_fs.glsl");

    int pointers[] = { 3, 3, 2 };
    vao_ = DrawerHelper::GetVertexArrayObject(
        array_cube_normal_texture, sizeof(array_cube_normal_texture),
        pointers, sizeof(pointers) / sizeof(pointers[0])
    );
    // SetCleanColor(0.0f, 0.0f, 0.0f);

    texture_ = TextureManager::Instance().GetTexture("res\\container2.png");
    specular_texture_ = TextureManager::Instance().GetTexture("res\\container2_specular.png");
}

void LightmapDrawer::_Render()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glBindVertexArray(vao_);
    glUseProgram(program_);
    camera_.get()->SetProgram(program_);
    camera_.get()->Update();
    ShaderManager::Instance().SetVec3(program_, "viewPos", camera_.get()->pos());

    ShaderManager::Instance().SetVec3(program_, "light.ambient", light_.get()->ambient());
    ShaderManager::Instance().SetVec3(program_, "light.diffuse", light_.get()->diffuse());
    ShaderManager::Instance().SetVec3(program_, "light.specular", light_.get()->specular());
    ShaderManager::Instance().SetVec3(program_, "light.position", light_.get()->position());

    {
        ShaderManager::Instance().SetInt(program_, "material.diffuse", 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture_);
        ShaderManager::Instance().SetInt(program_, "material.specular", 1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specular_texture_);
        // ShaderManager::Instance().SetVec3(program_, "material.specular", glm::vec3(0.5f));
        ShaderManager::Instance().SetFloat(program_, "material.shininess", 64.0f);

        ShaderManager::Instance().SetMat4(program_, "model", glm::mat4(1.0f));

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}
