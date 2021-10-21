#include "scene/scenetexture.h"

#include "utils/helper.h"
#include "drawer/texturedrawer.h"

// SceneTexture::~SceneTexture()
// {
// }

// void SceneTexture::Enter()
// {
//     TextureDrawer* container_drawer = new TextureDrawer();
//     container_drawer->Init();
//     AddDrawer(container_drawer);

//     TextureDrawerTransformation* transformation_drawer = new TextureDrawerTransformation();
//     transformation_drawer->Init();
//     AddDrawer(transformation_drawer);

//     if (ui_)
//     {
//         ERROR("UI already exists!");
//         return;
//     }
//     ui_ = new TextureUI();

//     autoRotate(true);
//     rotateSpeed(1.0f);
//     rotateRadian(0.0f);
//     mixValue(0.2f);
//     scale(glm::vec3(1.0f));
// }

// void SceneTexture::Leave()
// {
//     Scene::Leave();
//     ui_->Close();
//     SAFE_DELETE(ui_)
// }

// void SceneTexture::mixValue(const float& value)
// {
//     mix_value_ = value;
//     for (auto drawer : drawers_)
//     {
//         TextureDrawer* _drawer = dynamic_cast<TextureDrawer*>(drawer);
//         if (_drawer)
//             _drawer->mixValue(mix_value_);
//     }
// }

// void SceneTexture::autoRotate(const bool& auto_rotate)
// {
//     auto_rotate_ = auto_rotate;
//     for (auto drawer : drawers_)
//     {
//         TextureDrawerTransformation* _drawer = dynamic_cast<TextureDrawerTransformation*>(drawer);
//         if (_drawer)
//             _drawer->autoRotate(auto_rotate_);
//     }
// }

// void SceneTexture::rotateSpeed(const float& rotate_speed)
// {
//     rotate_speed_ = rotate_speed;
//     for (auto drawer : drawers_)
//     {
//         TextureDrawerTransformation* _drawer = dynamic_cast<TextureDrawerTransformation*>(drawer);
//         if (_drawer)
//             _drawer->rotateSpeed(rotate_speed_);
//     }
// }

// void SceneTexture::rotateRadian(const float& rotate_radian)
// {
//     rotate_radian_ = rotate_radian;
//     for (auto drawer : drawers_)
//     {
//         TextureDrawerTransformation* _drawer = dynamic_cast<TextureDrawerTransformation*>(drawer);
//         if (_drawer)
//             _drawer->rotateRadian(rotate_radian_);
//     }
// }

// void SceneTexture::scale(const glm::vec3& _scale)
// {
//     scale_ = _scale;
//     for (auto drawer : drawers_)
//     {
//         TextureDrawerTransformation* _drawer = dynamic_cast<TextureDrawerTransformation*>(drawer);
//         if (_drawer)
//             _drawer->scale(scale_);
//     }
// }
