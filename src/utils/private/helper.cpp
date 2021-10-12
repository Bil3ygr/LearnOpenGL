#include "utils/public/helper.h"

#ifdef _WIN32
#include <Windows.h>
#include <debugapi.h>
#endif
#include <sys/stat.h>

#include <cstdarg>
#include <iostream>
#include <fstream>
#include <sstream>

#ifdef _WIN32
#define COLOR_GREEN "\x1b[1m\x1b[32m"
#define COLOR_YELLOW "\x1b[1m\x1b[33m"
#define COLOR_RED "\x1b[1m\x1b[31m"
#define COLOR_RESET "\x1b[0m"
#else
#define COLOR_GREEN ""
#define COLOR_YELLOW ""
#define COLOR_RED ""
#define COLOR_RESET ""
#endif

constexpr int MAX_STR_COUNT = 512;

bool MessageHandler::Print(const LogType& type, const char* str)
{
    switch(type)
    {
        case LogType::kInfo:
            return PrintInfo(str);
        case LogType::kWarning:
            return PrintWarning(str);
        case LogType::kError:
            return PrintError(str);
        case LogType::kDebug:
        default:
            return PrintDebug(str);
    }
}

bool MessageHandler::PrintDebug(const char* str)
{
    std::cout << str;	/* Default */
    return false;
}

bool MessageHandler::PrintInfo(const char* str)
{
    std::cout << COLOR_GREEN << str << COLOR_RESET;
    return false;
}

bool MessageHandler::PrintWarning(const char* str)
{
    std::cout << COLOR_YELLOW << str << COLOR_RESET;
    return false;
}

bool MessageHandler::PrintError(const char* str)
{
    std::cout << COLOR_RED << str << COLOR_RESET;
    return false;
}

DebugOutput::DebugOutput()
{
    msgHandler_ = new MessageHandler();
}

DebugOutput::~DebugOutput()
{
    SAFE_DELETE(msgHandler_);
}

void DebugOutput::PrintDebug(const char* str, ...)
{
    if (str == nullptr || !enableError_)
        return;

    char strCache[MAX_STR_COUNT];

    sprintf(strCache, "[DEBUG]:");
    const int pos = int(strlen(strCache));
    va_list ap;
    va_start(ap, str);
    vsnprintf(pos + strCache, MAX_STR_COUNT - 1, str, ap);
    va_end(ap);

    if (msgHandler_ && msgHandler_->Print(LogType::kDebug, strCache))
        return;

#ifdef _WIN32
    ::OutputDebugStringA(strCache);
#endif
}

void DebugOutput::PrintInfo(const char* str, ...)
{
    if (str == nullptr || !enableError_)
        return;

    char strCache[MAX_STR_COUNT];

    sprintf(strCache, "[INFO]:");
    const int pos = int(strlen(strCache));
    va_list ap;
    va_start(ap, str);
    vsnprintf(pos + strCache, MAX_STR_COUNT - 1, str, ap);
    va_end(ap);

    if (msgHandler_ && msgHandler_->Print(LogType::kInfo, strCache))
        return;

#ifdef _WIN32
    ::OutputDebugStringA(strCache);
#endif
    //PrintWarning()
}

void DebugOutput::PrintWarning(const char* str, ...)
{
    if (str == nullptr || !enableError_)
        return;

    char strCache[MAX_STR_COUNT];

    sprintf(strCache, "[WARNING]:");
    const int pos = int(strlen(strCache));
    va_list ap;
    va_start(ap, str);
    vsnprintf(pos + strCache, MAX_STR_COUNT - 1, str, ap);
    va_end(ap);

    if (msgHandler_ && msgHandler_->Print(LogType::kWarning, strCache))
        return;

#ifdef _WIN32
    ::OutputDebugStringA(strCache);
#endif
}

void DebugOutput::PrintError(const char* str, ...)
{
    if (str == nullptr || !enableError_)
        return;

    char strCache[MAX_STR_COUNT];

    sprintf(strCache, "[ERROR]:");
    const int pos = int(strlen(strCache));
    va_list ap;
    va_start(ap, str);
    vsnprintf(pos + strCache, MAX_STR_COUNT - 1, str, ap);
    va_end(ap);

    if (msgHandler_ && msgHandler_->Print(LogType::kError, strCache))
        return;

#ifdef _WIN32
    ::OutputDebugStringA(strCache);
#endif
}

const char* ReadFile(const char* filename)
{
    std::ifstream file(filename);
    if (file.good())
    {
        int filesize = 40960;
        char* content = (char*)malloc(sizeof(char) * filesize);
        if (content)
        {
            char buffer[1024];
            int pt = 0;
            while (file.getline(buffer, 1024))
            {
                for (int i = 0; i < 1024; ++i)
                {
                    char temp = buffer[i];
                    if (temp == '\0')
                    {
                        content[pt++] = '\n';
                        break;
                    }
                    content[pt++] = temp;
                }
            }
            content[pt] = '\0';
            char* result = (char*)malloc(sizeof(char) * (++pt));
            if (result)
            {
                std::memcpy(result, content, pt);
                return result;
            }
            ERROR("malloc size %s of char failed\n", TO_CHAR(pt));
        }
        ERROR("malloc size %s of char failed\n", TO_CHAR(filesize));
    }
    else
    {
        ERROR("read file [%s] failed\n", filename);
    }
    return nullptr;
}

// const char* ReadFile(const char* filename)
// {
//     std::string code;
//     std::ifstream file;
//     file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
//     try
//     {
//         file.open(filename);
//         std::stringstream stream;
//         stream << file.rdbuf();
//         file.close();
//         code = stream.str();
//     }
//     catch(std::ifstream::failure e)
//     {
//         ERROR("read file [%s] failed\n", filename);
//         return nullptr;
//     }
//     return code.c_str();
// }
