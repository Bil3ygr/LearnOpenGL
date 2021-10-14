#include "drawer/lightmapdrawer.h"

#include "utils/consts.h"
#include "utils/mousemanager.h"
#include "utils/texturemanager.h"

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
    glDisable(GL_DEPTH_TEST);
    camera_ = nullptr;
    light_ = nullptr;
    texture_ = 0;
    specular_texture_ = 0;
    MouseManager::Instance().buttonEnable(false);
}

void LightmapDrawer::Init()
{
    glEnable(GL_DEPTH_TEST);

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
    glClear(GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glBindVertexArray(vao_);
    glUseProgram(program_);
    camera_.get()->SetProgram(program_);
    camera_.get()->Update();
    ShaderManager::Instance().SetVec3(program_, "viewPos", camera_.get()->pos());

    ShaderManager::Instance().SetVec3(program_, "pointLight.ambient", light_.get()->ambient());
    ShaderManager::Instance().SetVec3(program_, "pointLight.diffuse", light_.get()->diffuse());
    ShaderManager::Instance().SetVec3(program_, "pointLight.specular", light_.get()->specular());
    ShaderManager::Instance().SetVec3(program_, "pointLight.position", light_.get()->position());

    ShaderManager::Instance().SetFloat(program_, "pointLight.constant", light_.get()->constant());

    {
        ShaderManager::Instance().SetInt(program_, "lightmapMaterial.diffuse", 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture_);
        ShaderManager::Instance().SetInt(program_, "lightmapMaterial.specular", 1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specular_texture_);
        ShaderManager::Instance().SetFloat(program_, "lightmapMaterial.shininess", 64.0f);

        ShaderManager::Instance().SetMat4(program_, "model", glm::mat4(1.0f));

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}
