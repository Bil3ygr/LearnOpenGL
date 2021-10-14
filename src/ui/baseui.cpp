#include "ui/baseui.h"

#include "ui/uimanager.h"

BaseUI::BaseUI()
{
    tag_ = UIManager::Instance().AddUI(this);
}

BaseUI::~BaseUI()
{
}

void BaseUI::Render()
{
}

void BaseUI::Close()
{
    if (tag_ == boost::uuids::nil_uuid())
        return;
    UIManager::Instance().DelUI(tag_);
}
