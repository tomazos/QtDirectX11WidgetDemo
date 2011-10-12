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
