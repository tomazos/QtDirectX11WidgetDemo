#ifndef DEVICE_H
#define DEVICE_H

#include "Global.h"

#include "Vertex.h"

FwdDeclShared(SwapChain);
FwdDeclShared(RenderTargetView);
FwdDeclShared(PixelShader);
FwdDeclShared(VertexShader);
FwdDeclShared(ShaderCode);
FwdDeclShared(InputLayout);
FwdDeclShared(VertexBuffer);
FwdDeclShared(Texture2d);

DeclShared(Device)
class Device : public LogWriter
{
public:
    ~Device();

    PRenderTargetView createRenderTargetView(PTexture2d);

    void setRenderTarget(PRenderTargetView);
    void setRenderTargetNone();

    void setupViewport(int iWidth, int iHeight);

    void clear(PRenderTargetView, float color[4]);
    void draw(int iVertexCount);

    PVertexBuffer createVertexBuffer(const QVector<Vertex>&);
    PVertexShader createVertexShader(PShaderCode);
    PPixelShader createPixelShader(PShaderCode);
    PInputLayout createInputLayout(PShaderCode);

    void setInputLayout(PInputLayout);
    void setVertexShader(PVertexShader);
    void setPixelShader(PPixelShader);
    void setVertexBuffer(PVertexBuffer);

private:
    friend class GraphicsInfrastructure;
    friend class Adapter;
    Device(Log*, ID3D11Device*, ID3D11DeviceContext*);

    ID3D11Device* m_pDevice;
    ID3D11DeviceContext* m_pContext;
};

#endif // DEVICE_H
