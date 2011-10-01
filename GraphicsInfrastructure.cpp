#include "GraphicsInfrastructure.h"

#include "Adapter.h"
#include "Device.h"
#include "SwapChain.h"

PGraphicsInfrastructure
GraphicsInfrastructure::create(Log* pLog)
{
    bool bOk;
    PGraphicsInfrastructure p(new GraphicsInfrastructure(bOk, pLog));

    if (bOk)
        return p;
    else
        return PGraphicsInfrastructure(0);
}

GraphicsInfrastructure::GraphicsInfrastructure(bool& bOk, Log* pLog)
    : LogWriter(pLog)
    , m_pFactory(0)
{
    HRESULT hr = CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**) &m_pFactory);
    bOk = SUCCEEDED(hr);
    if (!bOk)
        INFO(WinUtils::stringify(hr));
}

GraphicsInfrastructure::~GraphicsInfrastructure()
{
    if (m_pFactory)
        m_pFactory->Release();
}

PAdapter
GraphicsInfrastructure::getDefaultAdapter()
{
    IDXGIAdapter1* pAdapter(0);
    HRESULT hr = m_pFactory->EnumAdapters1(0, &pAdapter);
    if (FAILED(hr))
    {
        INFO(WinUtils::stringify(hr));
        return PAdapter(0);
    }
    return PAdapter(new Adapter(m_pLog, pAdapter));
}

PSwapChain GraphicsInfrastructure::createSwapChain(PDevice pDevice, HWND hwnd)
{
    DXGI_SWAP_CHAIN_DESC desc;
    ZeroMemory( &desc, sizeof( desc ) );
    desc.BufferDesc.Width = 0;
    desc.BufferDesc.Height = 0;
    desc.BufferDesc.RefreshRate.Numerator = 60;
    desc.BufferDesc.RefreshRate.Denominator = 1;
    desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.BufferCount = 1;
    desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    desc.OutputWindow = hwnd;
    desc.SampleDesc.Count = 8;
    desc.SampleDesc.Quality = 0;
    desc.Windowed = TRUE;

    IDXGISwapChain* pSwapChain(0);
    HRESULT hr = m_pFactory->CreateSwapChain(pDevice->m_pDevice, &desc, &pSwapChain);

    if (FAILED(hr))
    {
            INFO(WinUtils::stringify(hr));
            return PSwapChain(0);
    }

    return PSwapChain(new SwapChain(m_pLog, pSwapChain));
}
