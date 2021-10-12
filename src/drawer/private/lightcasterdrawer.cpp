#include "drawer/public/lightcasterdrawer.h"

#include "utils/public/consts.h"
#include "utils/public/mousemanager.h"
#include "utils/public/texturemanager.h"

LightcasterDrawer::LightcasterDrawer()
{
    camera_ = CameraManager::Instance().GetDefaultCamera();
    if (!camera_)
        camera_ = CameraManager::Instance().CreateCamera(0);
    light_ = nullptr;
    texture_ = 0;
    specular_texture_ = 0;
    MouseManager::Instance().buttonEnable(true);
}

LightcasterDrawer::~LightcasterDrawer()
{
    glDisable(GL_DEPTH_TEST);
    camera_ = nullptr;
    light_ = nullptr;
    texture_ = 0;
    specular_texture_ = 0;
    MouseManager::Instance().buttonEnable(false);
}

void LightcasterDrawer::Init()
{
    glEnable(GL_DEPTH_TEST);

    SetShader("shader\\lightmap_vs.glsl", "shader\\lightmap_fs.glsl");

    int pointers[] = { 3, 3, 2 };
    vao_ = DrawerHelper::GetVertexArrayObject(
        array_cube_normal_texture, sizeof(array_cube_normal_texture),
        pointers, sizeof(pointers) / sizeof(pointers[0])
    );

    texture_ = TextureManager::Instance().GetTexture("res\\container2.png");
    specular_texture_ = TextureManager::Instance().GetTexture("res\\container2_specular.png");
}

void LightcasterDrawer::_Render()
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

    {
        ShaderManager::Instance().SetInt(program_, "material.diffuse", 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture_);
        ShaderManager::Instance().SetInt(program_, "material.specular", 1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specular_texture_);
        // ShaderManager::Instance().SetVec3(program_, "material.specular", glm::vec3(0.5f));
        ShaderManager::Instance().SetFloat(program_, "material.shininess", 64.0f);

        glm::vec3 cubePositions[] = {
            glm::vec3( 0.0f,  0.0f,  0.0f),
            glm::vec3( 2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3( 2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3( 1.3f, -2.0f, -2.5f),
            glm::vec3( 1.5f,  2.0f, -2.5f),
            glm::vec3( 1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
        };
        glm::vec3 rotate = glm::vec3(1.0f, 0.3f, 0.5f);
        for (int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), cubePositions[i]);
            model = glm::rotate(model, glm::radians(20.0f * i), rotate);
            ShaderManager::Instance().SetMat4(program_, "model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
    }
}

void LightcasterPointLightDrawer::Init()
{
    glEnable(GL_DEPTH_TEST);

    SetShader("shader\\lightmap_vs.glsl", "shader\\lightcaster_pointlight_fs.glsl");

    int pointers[] = { 3, 3, 2 };
    vao_ = DrawerHelper::GetVertexArrayObject(
        array_cube_normal_texture, sizeof(array_cube_normal_texture),
        pointers, sizeof(pointers) / sizeof(pointers[0])
    );

    texture_ = TextureManager::Instance().GetTexture("res\\container2.png");
    specular_texture_ = TextureManager::Instance().GetTexture("res\\container2_specular.png");
}

void LightcasterPointLightDrawer::_Render()
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
    ShaderManager::Instance().SetVec3(program_, "light.position", glm::vec3(light_.get()->vector()));

    ShaderManager::Instance().SetFloat(program_, "light.constant", 1.0f);
    ShaderManager::Instance().SetFloat(program_, "light.linear", 0.09f);
    ShaderManager::Instance().SetFloat(program_, "light.quadratic", 0.032f);

    {
        ShaderManager::Instance().SetInt(program_, "material.diffuse", 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture_);
        ShaderManager::Instance().SetInt(program_, "material.specular", 1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specular_texture_);
        // ShaderManager::Instance().SetVec3(program_, "material.specular", glm::vec3(0.5f));
        ShaderManager::Instance().SetFloat(program_, "material.shininess", 64.0f);

        glm::vec3 cubePositions[] = {
            glm::vec3( 0.0f,  0.0f,  0.0f),
            glm::vec3( 2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3( 2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3( 1.3f, -2.0f, -2.5f),
            glm::vec3( 1.5f,  2.0f, -2.5f),
            glm::vec3( 1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
        };
        glm::vec3 rotate = glm::vec3(1.0f, 0.3f, 0.5f);
        for (int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), cubePositions[i]);
            model = glm::rotate(model, glm::radians(20.0f * i), rotate);
            ShaderManager::Instance().SetMat4(program_, "model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
    }
}

void LightcasterSpotLightDrawer::Init()
{
    glEnable(GL_DEPTH_TEST);

    SetShader("shader\\lightmap_vs.glsl", "shader\\lightcaster_spotlight_fs.glsl");

    int pointers[] = { 3, 3, 2 };
    vao_ = DrawerHelper::GetVertexArrayObject(
        array_cube_normal_texture, sizeof(array_cube_normal_texture),
        pointers, sizeof(pointers) / sizeof(pointers[0])
    );

    texture_ = TextureManager::Instance().GetTexture("res\\container2.png");
    specular_texture_ = TextureManager::Instance().GetTexture("res\\container2_specular.png");
}

void LightcasterSpotLightDrawer::_Render()
{
    glClear(GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glBindVertexArray(vao_);
    glUseProgram(program_);
    camera_.get()->SetProgram(program_);
    camera_.get()->Update();
    ShaderManager::Instance().SetVec3(program_, "viewPos", camera_.get()->pos());

    light_.get()->vector(glm::vec4(camera_.get()->pos(), 1.0f));
    light_.get()->lightDir(camera_.get()->front());

    ShaderManager::Instance().SetVec3(program_, "light.ambient", light_.get()->ambient());
    ShaderManager::Instance().SetVec3(program_, "light.diffuse", light_.get()->diffuse());
    ShaderManager::Instance().SetVec3(program_, "light.specular", light_.get()->specular());
    ShaderManager::Instance().SetVec3(program_, "light.position", glm::vec3(light_.get()->vector()));
    ShaderManager::Instance().SetVec3(program_, "light.direction", light_.get()->lightDir());
    ShaderManager::Instance().SetFloat(program_, "light.cutoff", glm::cos(light_.get()->cutoff()));
    ShaderManager::Instance().SetFloat(program_, "light.outtercutoff", glm::cos(light_.get()->outtercutoff()));

    ShaderManager::Instance().SetFloat(program_, "light.constant", 1.0f);
    ShaderManager::Instance().SetFloat(program_, "light.linear", 0.09f);
    ShaderManager::Instance().SetFloat(program_, "light.quadratic", 0.032f);

    {
        ShaderManager::Instance().SetInt(program_, "material.diffuse", 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture_);
        ShaderManager::Instance().SetInt(program_, "material.specular", 1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specular_texture_);
        // ShaderManager::Instance().SetVec3(program_, "material.specular", glm::vec3(0.5f));
        ShaderManager::Instance().SetFloat(program_, "material.shininess", 64.0f);

        glm::vec3 cubePositions[] = {
            glm::vec3( 0.0f,  0.0f,  0.0f),
            glm::vec3( 2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3( 2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3( 1.3f, -2.0f, -2.5f),
            glm::vec3( 1.5f,  2.0f, -2.5f),
            glm::vec3( 1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
        };
        glm::vec3 rotate = glm::vec3(1.0f, 0.3f, 0.5f);
        for (int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), cubePositions[i]);
            model = glm::rotate(model, glm::radians(20.0f * i), rotate);
            ShaderManager::Instance().SetMat4(program_, "model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
    }
}
