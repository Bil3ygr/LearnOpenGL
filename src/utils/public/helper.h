# pragma once

#ifndef SRC_UTILS_HELPER_H_
#define SRC_UTILS_HELPER_H_

#include <string>

#include "singleton.h"

enum class LogType
{
    kDebug,
    kInfo,
    kWarning,
    kError,
};

class  MessageHandler
{
public:
    virtual ~MessageHandler() {}
    virtual bool Print(const LogType& type, const char* str);
    virtual bool PrintDebug(const char* str);
    virtual bool PrintInfo(const char* str);
    virtual bool PrintWarning(const char* str);
    virtual bool PrintError(const char* str);
};

class DebugOutput : public Singleton<DebugOutput>
{
    friend class Singleton<DebugOutput>;
public:
    void PrintDebug(const char* str, ...);
    void PrintInfo(const char* str, ...);
    void PrintWarning(const char* str, ...);
    void PrintError(const char* str, ...);

private:
    DebugOutput();
    ~DebugOutput();

    MessageHandler* msgHandler_;

    bool enableDebug_ = true;
    bool enableInfo_ = true;
    bool enableWarning_ = true;
    bool enableError_ = true;
};

#define SAFE_DELETE(x) if (x)  { delete x; (x) = nullptr; }
#define DEBUG DebugOutput::Instance().PrintDebug
#define INFO DebugOutput::Instance().PrintInfo
#define WARNING DebugOutput::Instance().PrintWarning
#define ERROR DebugOutput::Instance().PrintError

#define TO_STR(x) std::to_string(x)
#define TO_CHAR(x) TO_STR(x).c_str()

const char* ReadFile(const char* filename);
#endif // !SRC_UTILS_HELPER_H_
