// (C) 2011, Andrew Tomazos <andrew@tomazos.com>.

#ifndef SWAPCHAIN_H
#define SWAPCHAIN_H

#include "Global.h"

FwdDeclShared(Texture2d);

DeclShared(SwapChain);
class SwapChain : public LogWriter
{
public:
    ~SwapChain();

    PTexture2d getBackBuffer();

    void present();
    void resize();

private:
    friend class GraphicsInfrastructure;
    SwapChain(Log*, IDXGISwapChain*);
    IDXGISwapChain* m_pSwapChain;
};

#endif // SWAPCHAIN_H
