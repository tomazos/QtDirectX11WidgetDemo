// (C) 2011, Andrew Tomazos <andrew@tomazos.com>.

#ifndef GRAPHICSINFRASTRUCTURE_H
#define GRAPHICSINFRASTRUCTURE_H

#include "Global.h"

FwdDeclShared(Adapter);
FwdDeclShared(SwapChain);
FwdDeclShared(Device);

DeclShared(GraphicsInfrastructure);
class GraphicsInfrastructure : public LogWriter
{
public:
    static PGraphicsInfrastructure create(Log* pLog);
    ~GraphicsInfrastructure();

    PAdapter getDefaultAdapter();

    PSwapChain createSwapChain(PDevice, HWND hwnd);

private:
    GraphicsInfrastructure(bool& bOk, Log*);
    IDXGIFactory1* m_pFactory;
};

#endif // GRAPHICSINFRASTRUCTURE_H
