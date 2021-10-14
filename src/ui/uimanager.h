#pragma once

#ifndef SRC_UTILS_UIMANAGER_H_
#define SRC_UTILS_UIMANAGER_H_

#include <map>

#include "baseui.h"
#include "utils/singleton.h"

class UIManager : public Singleton<UIManager>
{
    friend class Singleton<UIManager>;
    friend class BaseUI;
private:
    UIManager();
    ~UIManager();

    void Init();

    boost::uuids::uuid AddUI(BaseUI* ui);
    void DelUI(boost::uuids::uuid uuid);

public:
    void Render();

private:
    std::map<boost::uuids::uuid, BaseUI*> ui_list_;
};

#endif // !SRC_UTILS_UIMANAGER_H_
