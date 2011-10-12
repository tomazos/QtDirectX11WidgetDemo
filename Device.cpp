#include "Device.h"

#include "Texture2d.h"
#include "RenderTargetView.h"
#include "DepthStencilView.h"
#include "ShaderCode.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "InputLayout.h"
#include "Adapter.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "SwapChain.h"

Device::Device(Log* pLog, ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
    : LogWriter(pLog)
    , m_pDevice(pDevice)
    , m_pContext(pContext)
{

}

Device::~Device()
{
    if (m_pContext)
        m_pContext->Release();

    if (m_pDevice)
        m_pDevice->Release();
}

PRenderTargetView Device::createRenderTargetView(PTexture2d pTexture)
{
    ID3D11RenderTargetView* pView(0);
    HRESULT hr = m_pDevice->CreateRenderTargetView( pTexture->m_pTexture, NULL, &pView );
    if (FAILED(hr))
    {
        INFO(WinUtils::stringify(hr));
        return PRenderTargetView(0);
    }

    return PRenderTargetView(new RenderTargetView(m_pLog, pView));
}

void Device::setRenderTarget(PRenderTargetView pRenderTargetView, PDepthStencilView pDepthStencilView)
{
    m_pContext->OMSetRenderTargets(1, &pRenderTargetView->m_pView, pDepthStencilView->m_pView );
}

void Device::setRenderTargetNone()
{
    m_pContext->OMSetRenderTargets(0,0,0);
}

void Device::setupViewport(int iWidth, int iHeight)
{
    D3D11_VIEWPORT vp;
    vp.Width = iWidth;
    vp.Height = iHeight;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    m_pContext->RSSetViewports( 1, &vp );
}


void Device::clear(PRenderTargetView pView, float color[4])
{
    m_pContext->ClearRenderTargetView(pView->m_pView, color);
}

void Device::clear(PDepthStencilView pDepthStencilView)
{
    m_pContext->ClearDepthStencilView( pDepthStencilView->m_pView, D3D11_CLEAR_DEPTH, 1.0f, 0 );
}

PVertexShader Device::createVertexShader(PShaderCode pCode)
{
    PVertexShader pVertexShader(new VertexShader(m_pLog));
    HRESULT hr = m_pDevice->CreateVertexShader(pCode->m_pShaderCode->GetBufferPointer(), pCode->m_pShaderCode->GetBufferSize(), 0, &pVertexShader->m_pVertexShader);
    if (SUCCEEDED(hr))
        return pVertexShader;
    else
    {
        INFO(WinUtils::stringify(hr));
        return PVertexShader(0);
    }
}

PPixelShader Device::createPixelShader(PShaderCode pCode)
{
    PPixelShader pPixelShader(new PixelShader(m_pLog));
    HRESULT hr = m_pDevice->CreatePixelShader(pCode->m_pShaderCode->GetBufferPointer(), pCode->m_pShaderCode->GetBufferSize(), 0, &pPixelShader->m_pPixelShader);
    if (SUCCEEDED(hr))
        return pPixelShader;
    else
    {
        INFO(WinUtils::stringify(hr));
        return PPixelShader(0);
    }
}

PInputLayout Device::createInputLayout(PShaderCode pCode)
{
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },

    };

    UINT iNumElements = ARRAYSIZE( layout );

    PInputLayout pInputLayout(new InputLayout(m_pLog));
    HRESULT hr = m_pDevice->CreateInputLayout(layout, iNumElements, pCode->m_pShaderCode->GetBufferPointer(), pCode->m_pShaderCode->GetBufferSize(), &pInputLayout->m_pInputLayout);
    if (SUCCEEDED(hr))
        return pInputLayout;
    else
    {
        INFO(WinUtils::stringify(hr));
        return PInputLayout(0);
    }
}

void Device::setInputLayout(PInputLayout p)
{
    m_pContext->IASetInputLayout(p->m_pInputLayout);
}

void Device::setVertexShader(PVertexShader p)
{
    m_pContext->VSSetShader(p->m_pVertexShader,0,0);
}

void Device::setPixelShader(PPixelShader p)
{
    m_pContext->PSSetShader(p->m_pPixelShader,0,0);
}

PVertexBuffer Device::createVertexBuffer(const QVector<Vertex>& v)
{
    PVertexBuffer pBuffer(new VertexBuffer(m_pLog));

    D3D11_BUFFER_DESC bd;
    ZeroMemory( &bd, sizeof(bd) );
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof( Vertex ) * v.size();
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = 0;
    D3D11_SUBRESOURCE_DATA InitData;
    ZeroMemory( &InitData, sizeof(InitData) );
    InitData.pSysMem = v.data();
    HRESULT hr = m_pDevice->CreateBuffer( &bd, &InitData, &(pBuffer->m_pBuffer) );
    if (SUCCEEDED(hr))
        return pBuffer;
    else
    {
        INFO(WinUtils::stringify(hr));
        return PVertexBuffer(0);
    }
}

PIndexBuffer Device::createIndexBuffer(const QVector<quint16>& v)
{
    PIndexBuffer pBuffer(new IndexBuffer(m_pLog));

    D3D11_BUFFER_DESC bd;
    ZeroMemory( &bd, sizeof(bd) );
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof( quint32 ) * v.size();
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    bd.CPUAccessFlags = 0;
    D3D11_SUBRESOURCE_DATA InitData;
    ZeroMemory( &InitData, sizeof(InitData) );
    InitData.pSysMem = v.data();

    HRESULT hr = m_pDevice->CreateBuffer( &bd, &InitData, &(pBuffer->m_pBuffer) );

    if (SUCCEEDED(hr))
        return pBuffer;
    else
    {
        INFO(WinUtils::stringify(hr));
        return PIndexBuffer(0);
    }
}

PConstantBuffer Device::createConstantBufferSize(int iNumBytes)
{
    PConstantBuffer pBuffer(new ConstantBuffer(m_pLog, iNumBytes));

    D3D11_BUFFER_DESC bd;
    ZeroMemory( &bd, sizeof(bd) );
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = iNumBytes;
    bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    bd.CPUAccessFlags = 0;

    HRESULT hr = m_pDevice->CreateBuffer( &bd, NULL, &(pBuffer->m_pBuffer) );

    if (SUCCEEDED(hr))
        return pBuffer;
    else
    {
        INFO(WinUtils::stringify(hr));
        return PConstantBuffer(0);
    }
}

void Device::setVertexBuffer(PVertexBuffer pBuffer)
{
    UINT stride = sizeof( Vertex );
    UINT offset = 0;
    m_pContext->IASetVertexBuffers( 0, 1, &(pBuffer->m_pBuffer), &stride, &offset );
    m_pContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
}

void Device::setIndexBuffer(PIndexBuffer pBuffer)
{
    m_pContext->IASetIndexBuffer( pBuffer->m_pBuffer, DXGI_FORMAT_R16_UINT, 0 );
}

void Device::setConstantBufferSize(PConstantBuffer pBuffer, int iNumBytes, const void* pBufData)
{
    Q_UNUSED(iNumBytes);
    m_pContext->UpdateSubresource( pBuffer->m_pBuffer, 0, NULL, pBufData, 0, 0 );
    m_pContext->VSSetConstantBuffers( 0, 1, &(pBuffer->m_pBuffer) );
}

void Device::draw(int iVertexCount)
{
    m_pContext->Draw(iVertexCount,0);
}

void Device::drawIndexed(int iVertexCount)
{
    m_pContext->DrawIndexed(iVertexCount,0,0);
}

PTexture2d Device::createDepthStencil(int iHeight, int iWidth)
{
    PTexture2d pDepthStencil(new Texture2d(m_pLog, NULL));
    D3D11_TEXTURE2D_DESC descDepth;
    ZeroMemory( &descDepth, sizeof(descDepth) );
    descDepth.Width = iWidth;
    descDepth.Height = iHeight;
    descDepth.MipLevels = 1;
    descDepth.ArraySize = 1;
    descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    descDepth.SampleDesc.Count = 8;
    descDepth.SampleDesc.Quality = 0;
    descDepth.Usage = D3D11_USAGE_DEFAULT;
    descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    descDepth.CPUAccessFlags = 0;
    descDepth.MiscFlags = 0;
    HRESULT hr = m_pDevice->CreateTexture2D( &descDepth, NULL, &(pDepthStencil->m_pTexture));
    if (SUCCEEDED(hr))
        return pDepthStencil;
    else
    {
        INFO(WinUtils::stringify(hr));
        return PTexture2d(0);
    }
}

PDepthStencilView Device::createDepthStencilView(PTexture2d pDepthStencil)
{
    PDepthStencilView pDepthStencilView(new DepthStencilView(m_pLog, NULL));
    D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
    ZeroMemory( &descDSV, sizeof(descDSV) );
    descDSV.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
    descDSV.Texture2D.MipSlice = 0;
    HRESULT hr = m_pDevice->CreateDepthStencilView( pDepthStencil->m_pTexture, &descDSV, &(pDepthStencilView->m_pView) );
    if (SUCCEEDED(hr))
        return pDepthStencilView;
    else
    {
        INFO(WinUtils::stringify(hr));
        return PDepthStencilView(0);
    }
}
