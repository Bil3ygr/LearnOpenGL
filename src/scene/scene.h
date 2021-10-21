#  pragma once

#ifndef SRC_SCENE_SCENE_H_
#define SRC_SCENE_SCENE_H_

#include <vector>

#include "drawer/basedrawer.h"
#include "utils/helper.h"
#include "node/basenode.h"

 enum class SceneType
 {
     kUnknown,
     kDefault,
     kTriangle,
     kTexture,
     kSpace,
     kColor,
     kLightmap,
     kLightcaster,
 };

// inline char* SceneTypeToString(const SceneType& type)
// {
//     switch (type)
//     {
//     case SceneType::kTriangle:
//         return "Triangle";
//     case SceneType::kTexture:
//         return "Texture";
//     case SceneType::kSpace:
//         return "Space";
//     case SceneType::kColor:
//         return "Color";
//     case SceneType::kLightmap:
//         return "Lightmap";
//     case SceneType::kLightcaster:
//         return "Lightcaster";
//     case SceneType::kDefault:
//         return "Default";
//     case SceneType::kUnknown:
//     default:
//         return "Unknown";
//     }
// }

class Scene
{
public:
    Scene();
    virtual ~Scene();

    virtual const SceneType GetSceneType() { return type_; }
    virtual void Render();

    virtual void Enter();
    virtual void Leave();

    void AddDrawer(BaseDrawer* drawer);

    void cleanColor(const float& r, const float& g, const float& b, const float& a = 1.0f) { cleanColor(glm::vec4(r, g, b, a)); }
    void cleanColor(const glm::vec3& color) { cleanColor(glm::vec4(color, 1.0f)); }
    void cleanColor(const glm::vec4& color) { color_ = color; }
    const glm::vec4 cleanColor() const { return color_; }

    void AddNode(BaseNode* node);
    void DeleteNode(BaseNode* node);
    const std::vector<BaseNode*>& GetAllNodes() const { return nodes_; }
    const BaseNode* FindNodeByName(const std::string& name);
    std::vector<BaseNode> FindNodesByName(const std::string& name);

protected:
    std::vector<BaseDrawer*> drawers_;

private:
    const SceneType type_ = SceneType::kUnknown;
    glm::vec4 color_;
    std::vector<BaseNode*> nodes_;
    BaseNode* root_;
};

#endif // !SRC_SCENE_SCENE_H_
