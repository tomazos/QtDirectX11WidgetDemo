#ifndef IENGINEVIEW_H
#define IENGINEVIEW_H

#include "Global.h"

class Engine;

class IEngineView
{
public:
    virtual HWND EngineView_getHWND() = 0;
    virtual int EngineView_getWidth() = 0;
    virtual int EngineView_getHeight() = 0;
    virtual void EngineView_setEngine(Engine* pEngine) = 0;
};

#endif // IENGINEVIEW_H
