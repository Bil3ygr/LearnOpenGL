#include "scenetexture.h"

#include "node/triangle.h"
#include "node/texturenode.h"

void SceneTexture::RenderUI()
{

}

void SceneTexture::Enter()
{
    Triangle* triangle = new Triangle("Top Left");
    (*triangle)[0].vertex = glm::vec3(-1.0f, 0.0f, 0.0f);
    (*triangle)[0].color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    (*triangle)[1].vertex = glm::vec3(0.0f, 0.0f, 0.0f);
    (*triangle)[2].vertex = glm::vec3(-0.5f, 1.0f, 0.0f);
    AddNode(triangle);

    TextureNode* texture = new TextureNode("Texture");
    texture->SetTexture("res\\93365078_p1_master1200.png");
    AddNode(texture);
}
