#ifndef DEPTHSTENCILVIEW_H
#define DEPTHSTENCILVIEW_H

#include "Global.h"

DeclShared(DepthStencilView);
class DepthStencilView : public LogWriter
{
public:
    ~DepthStencilView();

private:
    friend class Device;
    DepthStencilView(Log*, ID3D11DepthStencilView*);

    ID3D11DepthStencilView* m_pView;
};

#endif // DEPTHSTENCILVIEW_H
