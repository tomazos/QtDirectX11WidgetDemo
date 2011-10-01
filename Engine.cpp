#include "Engine.h"

#include <QtCore/QTimer>

#include "GraphicsInfrastructure.h"
#include "Adapter.h"
#include "SwapChain.h"
#include "RenderTargetView.h"
#include "ShaderCode.h"
#include "IEngineView.h"
#include "Device.h"
#include "Texture2d.h"
#include "InputLayout.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "VertexBuffer.h"

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

    m_pRenderTargetView = m_pDevice->createRenderTargetView(m_pBackBuffer);
    if (!m_pRenderTargetView)
        return false;

    m_pDevice->setRenderTarget(m_pRenderTargetView);

    m_pDevice->setupViewport(m_pEngineView->EngineView_getWidth(), m_pEngineView->EngineView_getHeight());

    PShaderCode pVertexShaderCode(ShaderCode::compile(m_pLog, "Tutorial02.fx", "VS", "vs_4_0"));
    if (!pVertexShaderCode)
        return false;

    m_pInputLayout = m_pDevice->createInputLayout(pVertexShaderCode);

    m_pVertexShader = m_pDevice->createVertexShader(pVertexShaderCode);

    PShaderCode pPixelShaderCode(ShaderCode::compile(m_pLog, "Tutorial02.fx", "PS", "ps_4_0"));
    if (!pPixelShaderCode)
        return false;

    m_pPixelShader = m_pDevice->createPixelShader(pPixelShaderCode);

    m_pDevice->setInputLayout( m_pInputLayout );
    m_pDevice->setVertexShader( m_pVertexShader );
    m_pDevice->setPixelShader( m_pPixelShader );

    QVector<Vertex> v;
    v.push_back(Vertex(1, -1, 0.5));
    v.push_back(Vertex(-1, -1, 0.5));
    v.push_back(Vertex(-1, 1, 0.5));

    PVertexBuffer pVertexBuffer = m_pDevice->createVertexBuffer(v);

    m_pDevice->setVertexBuffer(pVertexBuffer);

    m_pEngineView->EngineView_setEngine(this);

    tickAsap();
    tickSec();
    return true;
}

void Engine::resize()
{
    m_pDevice->setRenderTargetNone();

    m_pRenderTargetView.clear();

    m_pBackBuffer.clear();

    m_pSwapChain->resize();

    m_pBackBuffer = m_pSwapChain->getBackBuffer();
    if (!m_pBackBuffer)
        return;

    m_pRenderTargetView = m_pDevice->createRenderTargetView(m_pBackBuffer);

    m_pDevice->setRenderTarget(m_pRenderTargetView);

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

    m_pDevice->draw(3);

    m_pSwapChain->present();
}

Engine::~Engine()
{
    m_pEngineView->EngineView_setEngine(0);
}
