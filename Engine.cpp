#include "Engine.h"

#include <QtCore/QTimer>

#include "GraphicsInfrastructure.h"
#include "Adapter.h"
#include "SwapChain.h"
#include "RenderTargetView.h"
#include "DepthStencilView.h"
#include "ShaderCode.h"
#include "IEngineView.h"
#include "Device.h"
#include "Texture2d.h"
#include "InputLayout.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"

PEngine Engine::create(Log* pLog, IEngineView* pView)
{
    PEngine pEngine(new Engine(pLog, pView));

    if (pEngine->init())
        return pEngine;
    else
        return PEngine(0);
}

Engine::Engine(Log* pLog, IEngineView* pView)
    : LogWriter(pLog)
    , m_pEngineView(pView)
    , m_iTicks(0)
    , m_iTicksPerSec(0)
{

}

struct Matricies
{
        XMMATRIX world;
        XMMATRIX view;
        XMMATRIX projection;
};

bool Engine::init()
{
    m_pInfrastructure = GraphicsInfrastructure::create(m_pLog);
    if (!m_pInfrastructure)
        return false;

    m_pAdapter = m_pInfrastructure->getDefaultAdapter();
    if (!m_pAdapter)
        return false;

    m_pDevice = m_pAdapter->createDevice();
    if (!m_pDevice)
        return false;

    m_pSwapChain = m_pInfrastructure->createSwapChain(m_pDevice, m_pEngineView->EngineView_getHWND());
    if (!m_pSwapChain)
        return false;

    m_pBackBuffer = m_pSwapChain->getBackBuffer();
    if (!m_pBackBuffer)
        return false;

    m_iHeight = m_pBackBuffer->height();
    m_iWidth = m_pBackBuffer->width();

    m_pRenderTargetView = m_pDevice->createRenderTargetView(m_pBackBuffer);
    if (!m_pRenderTargetView)
        return false;

    m_pDepthStencil = m_pDevice->createDepthStencil(m_iHeight, m_iWidth);
    if (!m_pDepthStencil)
        return false;

    m_pDepthStencilView = m_pDevice->createDepthStencilView(m_pDepthStencil);
    if (!m_pDepthStencilView)
        return false;

    m_pDevice->setRenderTarget(m_pRenderTargetView, m_pDepthStencilView);

    m_pDevice->setupViewport(m_pEngineView->EngineView_getWidth(), m_pEngineView->EngineView_getHeight());

    PShaderCode pVertexShaderCode(ShaderCode::compile(m_pLog, "Shaders.fx", "VS", "vs_4_0"));
    if (!pVertexShaderCode)
        return false;

    m_pInputLayout = m_pDevice->createInputLayout(pVertexShaderCode);

    m_pVertexShader = m_pDevice->createVertexShader(pVertexShaderCode);

    PShaderCode pPixelShaderCode(ShaderCode::compile(m_pLog, "Shaders.fx", "PS", "ps_4_0"));
    if (!pPixelShaderCode)
        return false;

    m_pPixelShader = m_pDevice->createPixelShader(pPixelShaderCode);

    m_pDevice->setInputLayout( m_pInputLayout );
    m_pDevice->setVertexShader( m_pVertexShader );
    m_pDevice->setPixelShader( m_pPixelShader );

    QVector<Vertex> v;
    v.push_back(Vertex( -1,  1, -1 , 0, 0, 1, 1 ));
    v.push_back(Vertex(  1,  1, -1,  0, 1, 0, 1 ));
    v.push_back(Vertex(  1,  1,  1 , 0, 1, 1, 1 ));
    v.push_back(Vertex( -1,  1,  1 , 1, 0, 0, 1 ));

    v.push_back(Vertex( -1, -1, -1 , 1, 0, 1, 1 ));
    v.push_back(Vertex(  1, -1, -1 , 1, 1, 0, 1 ));
    v.push_back(Vertex(  1, -1,  1 , 1, 1, 1, 1 ));
    v.push_back(Vertex( -1, -1,  1 , 0, 0, 0, 1 ));

    PVertexBuffer pVertexBuffer = m_pDevice->createVertexBuffer(v);
    if (!pVertexBuffer)
        return false;

    m_pDevice->setVertexBuffer(pVertexBuffer);

    QVector<quint16> v2;
    quint16 indices[] =
    {
        3,1,0,
        2,1,3,

        0,5,4,
        1,5,0,

        3,4,7,
        0,4,3,

        1,6,5,
        2,6,1,

        2,7,6,
        3,7,2,

        6,4,5,
        7,4,6,
    };

    for (int i = 0; i < 36; i++)
        v2.push_back(indices[i]);

    PIndexBuffer pIndexBuffer = m_pDevice->createIndexBuffer(v2);
    if (!pIndexBuffer)
        return false;

    m_pDevice->setIndexBuffer(pIndexBuffer);

    m_pConstantBuffer = m_pDevice->createConstantBuffer<Matricies>();

    m_pEngineView->EngineView_setEngine(this);

    tickAsap();
    tickSec();
    return true;
}

void Engine::resize()
{
    m_pDevice->setRenderTargetNone();

    m_pRenderTargetView.clear();
    m_pDepthStencilView.clear();
    m_pDepthStencil.clear();
    m_pBackBuffer.clear();

    m_pSwapChain->resize();

    m_pBackBuffer = m_pSwapChain->getBackBuffer();
    if (!m_pBackBuffer)
        return;

    m_iHeight = m_pBackBuffer->height();
    m_iWidth = m_pBackBuffer->width();

    m_pRenderTargetView = m_pDevice->createRenderTargetView(m_pBackBuffer);
    if (!m_pRenderTargetView)
        return;

    m_pDepthStencil = m_pDevice->createDepthStencil(m_iHeight, m_iWidth);
    if (!m_pDepthStencil)
        return;

    m_pDepthStencilView = m_pDevice->createDepthStencilView(m_pDepthStencil);
    if (!m_pDepthStencilView)
        return;

    m_pDevice->setRenderTarget(m_pRenderTargetView, m_pDepthStencilView);

    m_pDevice->setupViewport(m_pEngineView->EngineView_getWidth(), m_pEngineView->EngineView_getHeight());

    update();
}

void Engine::tickAsap()
{
    m_iTicks++;
    update();
    QTimer::singleShot(0, this, SLOT(tickAsap()));
}

void Engine::tickSec()
{
    m_iTicksPerSec = m_iTicks;
    m_iTicks = 0;

    INFO(QString("FPS = %1").arg(m_iTicksPerSec));
    QTimer::singleShot(1000, this, SLOT(tickSec()));
}

void Engine::update()
{
    float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red,green,blue,alpha

    m_pDevice->clear( m_pRenderTargetView, ClearColor );
    m_pDevice->clear( m_pDepthStencilView );

    Matricies m;
    XMVECTOR Eye = XMVectorSet( 0.0f, 1.0f, -5.0f, 0.0f );
    XMVECTOR At = XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );
    XMVECTOR Up = XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );
    m.world = XMMatrixTranspose( XMMatrixRotationY( GetTickCount() / 1000.0) );
    m.view = XMMatrixTranspose( XMMatrixLookAtLH( Eye, At, Up ));
    m.projection = XMMatrixTranspose( XMMatrixPerspectiveFovLH( XM_PIDIV2, m_iWidth / float(m_iHeight), 0.01f, 100.0f ));

    m_pDevice->setConstantBuffer(m_pConstantBuffer, m);

    m_pDevice->drawIndexed(36);

    m_pSwapChain->present();
}

Engine::~Engine()
{
    m_pEngineView->EngineView_setEngine(0);
}
