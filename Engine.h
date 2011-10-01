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
FwdDeclShared(ShaderCode);
FwdDeclShared(InputLayout);
FwdDeclShared(VertexShader);
FwdDeclShared(PixelShader);

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
    PRenderTargetView m_pRenderTargetView;
    IEngineView* m_pEngineView;

    PInputLayout m_pInputLayout;
    PVertexShader m_pVertexShader;
    PPixelShader m_pPixelShader;

    quint64 m_iTicks;
    quint64 m_iTicksPerSec;
};

#endif // ENGINE_H
