// (C) 2011, Andrew Tomazos <andrew@tomazos.com>.

#ifndef ENGINE_H
#define ENGINE_H

#include "Global.h"

class IEngineView;

FwdDeclShared(GraphicsInfrastructure);
FwdDeclShared(Adapter);
FwdDeclShared(Device);
FwdDeclShared(SwapChain);
FwdDeclShared(Texture2d);
FwdDeclShared(RenderTargetView);
FwdDeclShared(DepthStencilView);
FwdDeclShared(ShaderCode);
FwdDeclShared(InputLayout);
FwdDeclShared(VertexShader);
FwdDeclShared(PixelShader);
FwdDeclShared(ConstantBuffer);

DeclShared(Engine);
class Engine : public QObject, public LogWriter
{
    Q_OBJECT

public:
    static PEngine create(Log*, IEngineView*);

    ~Engine();

    void resize();

    void update();

public slots:
    void tickAsap();
    void tickSec();

private:
    Engine(Log*, IEngineView*);

    bool init();

    PGraphicsInfrastructure m_pInfrastructure;
    PAdapter m_pAdapter;
    PDevice m_pDevice;
    PSwapChain m_pSwapChain;
    PTexture2d m_pBackBuffer;
    PTexture2d m_pDepthStencil;
    PRenderTargetView m_pRenderTargetView;
    PDepthStencilView m_pDepthStencilView;
    IEngineView* m_pEngineView;

    PInputLayout m_pInputLayout;
    PVertexShader m_pVertexShader;
    PPixelShader m_pPixelShader;
    PConstantBuffer m_pConstantBuffer;

    int m_iHeight;
    int m_iWidth;

    quint64 m_iTicks;
    quint64 m_iTicksPerSec;
};

#endif // ENGINE_H
