#pragma once

#ifndef SRC_DRAWER_TRIANGLEDRAWER_H_
#define SRC_DRAWER_TRIANGLEDRAWER_H_

#include "basedrawer.h"

class TriangleDrawer : public BaseDrawer
{
public:
    virtual void Init();

protected:
    virtual void _Render() override;
};

class TriangleDrawerPractice : public TriangleDrawer
{
public:
    void Init() override final;
};

class TriangleDrawerWithTimeColor : public TriangleDrawer
{
public:
    void Init() override final;

protected:
    void _Render() override final;
};

class TriangleDrawerWithInitColor : public TriangleDrawer
{
public:
    void Init() override final;
};

class TriangleDrawerWithInitColorPractice : public TriangleDrawer
{
public:
    void Init() override final;

protected:
    void _Render() override final;
};

#endif // !SRC_DRAWER_TRIANGLEDRAWER_H_
