#pragma once

#ifndef SRC_UTILS_TIMEMANAGER_H_
#define SRC_UTILS_TIMEMANAGER_H_

#include "singleton.h"

class TimeManager : public Singleton<TimeManager>
{
    friend class Singleton<TimeManager>;
private:
    TimeManager();
    ~TimeManager();

public:
    void deltaTime(const float& time) { delta_time_ = time; }
    const float& deltaTime() const { return delta_time_; }

private:
    float delta_time_;
};

#endif // !SRC_UTILS_TIMEMANAGER_H_
