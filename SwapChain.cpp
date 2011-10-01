#include "SwapChain.h"

#include "Texture2d.h"

SwapChain::SwapChain(Log* pLog, IDXGISwapChain* pSwapChain)
    : LogWriter(pLog)
    , m_pSwapChain(pSwapChain)
{
}

SwapChain::~SwapChain()
{
    if (m_pSwapChain)
        m_pSwapChain->Release();
}

PTexture2d SwapChain::getBackBuffer()
{
    ID3D11Texture2D* pBackBuffer = NULL;

    HRESULT hr = m_pSwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )&pBackBuffer );
    if( FAILED( hr ) )
    {
        INFO(WinUtils::stringify(hr));
        return PTexture2d(0);
    }

    return PTexture2d(new Texture2d(m_pLog, pBackBuffer));
}

void SwapChain::present()
{
    m_pSwapChain->Present(0, 0);
}

void SwapChain::resize()
{
    m_pSwapChain->ResizeBuffers(0,0,0,DXGI_FORMAT_UNKNOWN,0);
}
