// (C) 2011, Andrew Tomazos <andrew@tomazos.com>.

#include "DepthStencilView.h"

DepthStencilView::~DepthStencilView()
{
    if (m_pView)
        m_pView->Release();
}

DepthStencilView::DepthStencilView(Log* pLog, ID3D11DepthStencilView* pView)
    : LogWriter(pLog)
    , m_pView(pView)
{

}
