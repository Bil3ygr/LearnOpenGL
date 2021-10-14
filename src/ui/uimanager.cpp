#include "ui/uimanager.h"

#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "mainwindow.h"
#include "utils/helper.h"

UIManager::UIManager()
{
    ui_list_ = std::map<boost::uuids::uuid, BaseUI*>();

    Init();
}

UIManager::~UIManager()
{
    while (!ui_list_.empty())
        ui_list_.begin()->second->Close();
}

void UIManager::Init()
{
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(const_cast<GLFWwindow*>(MainWindow::Instance().window()), true);
    ImGui_ImplOpenGL3_Init("#version 460");
}

boost::uuids::uuid UIManager::AddUI(BaseUI* ui)
{
    boost::uuids::uuid uuid = boost::uuids::random_generator()();
    auto iter = ui_list_.find(uuid);
    if (iter != ui_list_.end())
    {
        WARNING("UI [%s] already exists, add failed\n", boost::lexical_cast<std::string>(uuid).c_str());
        return boost::uuids::nil_uuid();
    }

    ui_list_[uuid] = ui;
    return uuid;
}

void UIManager::DelUI(boost::uuids::uuid uuid)
{
    auto iter = ui_list_.find(uuid);
    if (iter == ui_list_.end())
    {
        WARNING("UI [%s] not found, delete failed\n", boost::lexical_cast<std::string>(uuid).c_str());
        return;
    }

    ui_list_.erase(iter);
}

void UIManager::Render()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    for (auto iter = ui_list_.begin(); iter != ui_list_.end(); ++iter)
    {
        if (iter->second->visible())
            iter->second->Render();
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
