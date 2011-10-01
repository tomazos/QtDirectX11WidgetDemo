#include "RenderTargetView.h"

RenderTargetView::~RenderTargetView()
{
    if (m_pView)
        m_pView->Release();
}

RenderTargetView::RenderTargetView(Log* pLog, ID3D11RenderTargetView* pRenderTargetView)
    : LogWriter(pLog)
    , m_pView(pRenderTargetView)
{

}
