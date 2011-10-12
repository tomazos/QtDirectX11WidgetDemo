// (C) 2011, Andrew Tomazos <andrew@tomazos.com>.

#ifndef DEVICE_H
#define DEVICE_H

#include "Global.h"

#include "Vertex.h"

FwdDeclShared(SwapChain);
FwdDeclShared(RenderTargetView);
FwdDeclShared(DepthStencilView);
FwdDeclShared(PixelShader);
FwdDeclShared(VertexShader);
FwdDeclShared(ShaderCode);
FwdDeclShared(InputLayout);
FwdDeclShared(VertexBuffer);
FwdDeclShared(IndexBuffer);
FwdDeclShared(ConstantBuffer);
FwdDeclShared(Texture2d);

DeclShared(Device)
class Device : public LogWriter
{
public:
    ~Device();

    PRenderTargetView createRenderTargetView(PTexture2d);

    PTexture2d createDepthStencil(int iHeight, int iWidth);
    PDepthStencilView createDepthStencilView(PTexture2d pDepthStencil);

    void setRenderTarget(PRenderTargetView, PDepthStencilView);
    void setRenderTargetNone();

    void setupViewport(int iWidth, int iHeight);

    void clear(PRenderTargetView, float color[4]);
    void clear(PDepthStencilView);

    void draw(int iVertexCount);
    void drawIndexed(int iVertexCount);

    PVertexBuffer createVertexBuffer(const QVector<Vertex>&);
    PIndexBuffer createIndexBuffer(const QVector<quint16>&);

    template <class T>
    PConstantBuffer createConstantBuffer() { return createConstantBufferSize(sizeof(T)); }

    template <class T>
    void setConstantBuffer(PConstantBuffer pBuf, const T& buf) { setConstantBufferSize(pBuf, sizeof(T), &buf); }

    PVertexShader createVertexShader(PShaderCode);
    PPixelShader createPixelShader(PShaderCode);
    PInputLayout createInputLayout(PShaderCode);

    void setInputLayout(PInputLayout);
    void setVertexShader(PVertexShader);
    void setPixelShader(PPixelShader);
    void setVertexBuffer(PVertexBuffer);
    void setIndexBuffer(PIndexBuffer);

private:
    PConstantBuffer createConstantBufferSize(int iBytes);
    void setConstantBufferSize(PConstantBuffer pBuf, int iBytes, const void* pBufData);

    friend class GraphicsInfrastructure;
    friend class Adapter;
    Device(Log*, ID3D11Device*, ID3D11DeviceContext*);

    ID3D11Device* m_pDevice;
    ID3D11DeviceContext* m_pContext;
};

#endif // DEVICE_H
