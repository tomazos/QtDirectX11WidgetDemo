// (C) 2011, Andrew Tomazos <andrew@tomazos.com>.

#ifndef RENDERTARGETVIEW_H
#define RENDERTARGETVIEW_H

#include "Global.h"

DeclShared(RenderTargetView);
class RenderTargetView : public LogWriter
{
public:
    ~RenderTargetView();

private:
    friend class Device;
    RenderTargetView(Log*, ID3D11RenderTargetView*);

    ID3D11RenderTargetView* m_pView;
};

#endif // RENDERTARGETVIEW_H
