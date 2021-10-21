#include "scenetriangle.h"

#include "imgui.h"

#include "node/triangle.h"
#include "node/rectangle.h"

void SceneTriangle::RenderUI()
{
    BaseNode* node = const_cast<BaseNode*>(FindNodeByName("Top Left"));
    if (node)
    {
        Triangle* triangle = dynamic_cast<Triangle*>(node);
        if (triangle)
        {
            ImGui::Text("Top Left Triangle");
            VertexInfo tv = (*triangle)[0];
            bool update = false;
            ImVec4 v1_color = ImVec4(tv.color.r, tv.color.g, tv.color.b, tv.color.a);
            if (ImGui::ColorEdit4("Vertex1", (float*)&v1_color, ImGuiColorEditFlags_NoInputs))
            {
                (*triangle)[0].color = glm::vec4(v1_color.x, v1_color.y, v1_color.z, v1_color.w);
                update = true;
            }
            ImGui::SameLine();
            tv = (*triangle)[1];
            ImVec4 v2_color = ImVec4(tv.color.r, tv.color.g, tv.color.b, tv.color.a);
            if (ImGui::ColorEdit4("Vertex2", (float*)&v2_color, ImGuiColorEditFlags_NoInputs))
            {
                (*triangle)[1].color = glm::vec4(v2_color.x, v2_color.y, v2_color.z, v2_color.w);
                update = true;
            }
            ImGui::SameLine();
            tv = (*triangle)[2];
            ImVec4 v3_color = ImVec4(tv.color.r, tv.color.g, tv.color.b, tv.color.a);
            if (ImGui::ColorEdit4("Vertex3", (float*)&v3_color, ImGuiColorEditFlags_NoInputs))
            {
                (*triangle)[2].color = glm::vec4(v3_color.x, v3_color.y, v3_color.z, v3_color.w);
                update = true;
            }

            if (update)
                triangle->update();
        }
    }

    node = const_cast<BaseNode*>(FindNodeByName("Top Right"));
    if (node)
    {
        Triangle* triangle = dynamic_cast<Triangle*>(node);
        if (triangle)
        {
            ImGui::Text("Top Right Triangle");
            float dynamic_y = abs(sin(glfwGetTime()));

            VertexInfo tv = (*triangle)[0];
            ImGui::Text("Vertex1: (%.2f, %.2f, %.2f)", tv.vertex.x, dynamic_y + 1.0, tv.vertex.z);
            (*triangle)[0].vertex = glm::vec3(tv.vertex.x, dynamic_y + 1.0f, tv.vertex.z);
            tv = (*triangle)[1];
            ImGui::Text("Vertex2: (%.2f, %.2f, %.2f)", tv.vertex.x, dynamic_y, tv.vertex.z);
            (*triangle)[1].vertex = glm::vec3(tv.vertex.x, dynamic_y, tv.vertex.z);
            tv = (*triangle)[2];
            ImGui::Text("Vertex3: (%.2f, %.2f, %.2f)", tv.vertex.x, dynamic_y, tv.vertex.z);
            (*triangle)[2].vertex = glm::vec3(tv.vertex.x, dynamic_y, tv.vertex.z);

            triangle->update();
        }
    }

    node = const_cast<BaseNode*>(FindNodeByName("Bottom Right"));
    if (node)
    {
        Rectangle* rectangle = dynamic_cast<Rectangle*>(node);
        if (rectangle)
        {
            ImGui::Text("Bottom Right Rectangle");
            bool line_mode = rectangle->line_mode();
            if (ImGui::Checkbox("Line mode", &line_mode))
                rectangle->line_mode(line_mode);
        }
    }
}

void SceneTriangle::Enter()
{
    Triangle* triangle = new Triangle("Top Left");
    (*triangle)[0].vertex = glm::vec3(-1.0f, 0.0f, 0.0f);
    (*triangle)[0].color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    (*triangle)[1].vertex = glm::vec3(0.0f, 0.0f, 0.0f);
    (*triangle)[2].vertex = glm::vec3(-0.5f, 1.0f, 0.0f);
    AddNode(triangle);

    triangle = new Triangle("Top Right");
    (*triangle)[0].vertex = glm::vec3(0.5f, 1.0f, 0.0f);
    (*triangle)[0].color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    (*triangle)[1].vertex = glm::vec3(0.0f, 0.0f, 0.0f);
    (*triangle)[1].color = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
    (*triangle)[2].vertex = glm::vec3(1.0f, 0.0f, 0.0f);
    (*triangle)[2].color = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
    AddNode(triangle);

    Rectangle* rectangle = new Rectangle("Bottom Right");
    (*rectangle)[0].vertex = glm::vec3(0.0f, 0.0f, 0.0f);
    (*rectangle)[0].color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    (*rectangle)[1].vertex = glm::vec3(0.0f, -1.0f, 0.0f);
    (*rectangle)[1].color = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
    (*rectangle)[2].vertex = glm::vec3(1.0f, -1.0f, 0.0f);
    (*rectangle)[2].color = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
    (*rectangle)[3].vertex = glm::vec3(1.0f, 0.0f, 0.0f);
    (*rectangle)[3].color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    AddNode(rectangle);
}
