#include "Adapter.h"

#include "Device.h"

Adapter::Adapter(Log* pLog, IDXGIAdapter1* pAdapter)
    : LogWriter(pLog)
    , m_pAdapter(pAdapter)
{

}

Adapter::~Adapter()
{
    m_pAdapter->Release();
}

PDevice Adapter::createDevice()
{
    D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0 };

    D3D_FEATURE_LEVEL featureLevel;

    ID3D11Device* pDevice(0);
    ID3D11DeviceContext* pContext(0);
    HRESULT hr = D3D11CreateDevice(m_pAdapter, D3D_DRIVER_TYPE_UNKNOWN, NULL,
                                   D3D11_CREATE_DEVICE_DEBUG, featureLevels, 1, D3D11_SDK_VERSION,
                                   &pDevice, &featureLevel, &pContext);

    if (FAILED(hr))
    {
        INFO(WinUtils::stringify(hr));
        return PDevice(0);
    }

    ASSERT(featureLevel == D3D_FEATURE_LEVEL_11_0);
    return PDevice(new Device(m_pLog, pDevice, pContext));
}
