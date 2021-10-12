#pragma once

#ifndef SRC_UTILS_SINGLETON_H_
#define SRC_UTILS_SINGLETON_H_

template <class T>
class Singleton
{
public:
    Singleton(Singleton const &) = delete;
    void operator=(Singleton const &) = delete;

    static T& Instance()
    {
        static T instance;
        return instance;
    }

    virtual ~Singleton() {}

protected:
    Singleton() {}
};

#endif // !SRC_UTILS_SINGLETON_H_
