// (C) 2011, Andrew Tomazos <andrew@tomazos.com>.

#ifndef ADAPTER_H
#define ADAPTER_H

#include "Global.h"

FwdDeclShared(Device);

DeclShared(Adapter);
class Adapter : public LogWriter
{
public:
    ~Adapter();

    PDevice createDevice();

private:
    friend class GraphicsInfrastructure;
    Adapter(Log*, IDXGIAdapter1*);
    IDXGIAdapter1* m_pAdapter;
};

#endif // ADAPTER_H
