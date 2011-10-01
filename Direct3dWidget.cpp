#include "Direct3dWidget.h"

#include <QtCore/QTimer>

#include "Engine.h"

Direct3dWidget::Direct3dWidget(QWidget *parent)
    : QWidget(parent)
    , m_pEngine(0)
{
    setUpdatesEnabled(false);
}

void Direct3dWidget::resizeEvent(QResizeEvent*)
{
    if (m_pEngine)
    {
        m_pEngine->resize();
    }
}


//class D3D
//{
//public:
//    ID3D11Device*           g_pd3dDevice;
//    ID3D11DeviceContext*    g_pImmediateContext;
//    IDXGISwapChain*         g_pSwapChain;
//    ID3D11RenderTargetView* g_pRenderTargetView;
//    ID3D11VertexShader*     g_pVertexShader;
//    ID3D11PixelShader*      g_pPixelShader;
//    ID3D11InputLayout*      g_pVertexLayout;
//    ID3D11Buffer*           g_pVertexBuffer;
//    D3D_FEATURE_LEVEL       g_featureLevel;

//    D3D()
//        : g_pd3dDevice(0)
//        , g_pImmediateContext(0)
//        , g_pSwapChain(0)
//        , g_pRenderTargetView(0)
//        , g_pVertexShader(0)
//        , g_pPixelShader(0)
//        , g_pVertexLayout(0)
//        , g_pVertexBuffer(0)
//        , g_featureLevel(D3D_FEATURE_LEVEL_11_0)
//    {}

//    struct SimpleVertex
//    {
//        XMFLOAT3 Pos;
//    };

//    //--------------------------------------------------------------------------------------
//    // Helper for compiling shaders with D3DX11
//    //--------------------------------------------------------------------------------------
//    HRESULT CompileShaderFromFile( WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut )
//    {
//        HRESULT hr = S_OK;

//        DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
//    #if defined( DEBUG ) || defined( _DEBUG )
//        // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
//        // Setting this flag improves the shader debugging experience, but still allows
//        // the shaders to be optimized and to run exactly the way they will run in
//        // the release configuration of this program.
//        dwShaderFlags |= D3DCOMPILE_DEBUG;
//    #endif

//        ID3DBlob* pErrorBlob;
//        hr = D3DX11CompileFromFile( szFileName, NULL, NULL, szEntryPoint, szShaderModel,
//            dwShaderFlags, 0, NULL, ppBlobOut, &pErrorBlob, NULL );
//        if( FAILED(hr) )
//        {
//            if( pErrorBlob != NULL )
//                OutputDebugStringA( (char*)pErrorBlob->GetBufferPointer() );
//            if( pErrorBlob ) pErrorBlob->Release();
//            return hr;
//        }
//        if( pErrorBlob ) pErrorBlob->Release();

//        return S_OK;
//    }

//    HRESULT InitDevice(HWND hWnd)
//    {
//        HRESULT hr = S_OK;

//        RECT rc;
//        GetClientRect( hWnd, &rc );
//        UINT width = rc.right - rc.left;
//        UINT height = rc.bottom - rc.top;

//        UINT createDeviceFlags = 0;
//    #ifdef _DEBUG
//        createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
//    #endif

//        D3D_FEATURE_LEVEL featureLevels[] =
//        {
//            D3D_FEATURE_LEVEL_11_0,
//            D3D_FEATURE_LEVEL_10_1,
//            D3D_FEATURE_LEVEL_10_0,
//        };
//            UINT numFeatureLevels = ARRAYSIZE( featureLevels );

//        DXGI_SWAP_CHAIN_DESC sd;
//        ZeroMemory( &sd, sizeof( sd ) );
//        sd.BufferCount = 1;
//        sd.BufferDesc.Width = width;
//        sd.BufferDesc.Height = height;
//        sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
//        sd.BufferDesc.RefreshRate.Numerator = 60;
//        sd.BufferDesc.RefreshRate.Denominator = 1;
//        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
//        sd.OutputWindow = hWnd;
//        sd.SampleDesc.Count = 1;
//        sd.SampleDesc.Quality = 0;
//        sd.Windowed = TRUE;

//        hr = D3D11CreateDeviceAndSwapChain( NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
//                                            D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &g_featureLevel, &g_pImmediateContext );
//        if( FAILED( hr ) )
//            return hr;

//        // Create a render target view
//        ID3D11Texture2D* pBackBuffer = NULL;
//        hr = g_pSwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )&pBackBuffer );
//        if( FAILED( hr ) )
//            return hr;

//        hr = g_pd3dDevice->CreateRenderTargetView( pBackBuffer, NULL, &g_pRenderTargetView );
//        pBackBuffer->Release();
//        if( FAILED( hr ) )
//            return hr;

//        g_pImmediateContext->OMSetRenderTargets( 1, &g_pRenderTargetView, NULL );

//        // Setup the viewport
//        D3D11_VIEWPORT vp;
//        vp.Width = (FLOAT)width;
//        vp.Height = (FLOAT)height;
//        vp.MinDepth = 0.0f;
//        vp.MaxDepth = 1.0f;
//        vp.TopLeftX = 0;
//        vp.TopLeftY = 0;
//        g_pImmediateContext->RSSetViewports( 1, &vp );

//        // Compile the vertex shader
//        ID3DBlob* pVSBlob = NULL;
//        hr = CompileShaderFromFile( L"Tutorial02.fx", "VS", "vs_4_0", &pVSBlob );
//        if( FAILED( hr ) )
//        {
//            MessageBox( NULL,
//                        L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK );
//            return hr;
//        }

//            // Create the vertex shader
//            hr = g_pd3dDevice->CreateVertexShader( pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), NULL, &g_pVertexShader );
//            if( FAILED( hr ) )
//            {
//                    pVSBlob->Release();
//            return hr;
//            }

//        // Define the input layout
//        D3D11_INPUT_ELEMENT_DESC layout[] =
//        {
//            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//        };
//            UINT numElements = ARRAYSIZE( layout );

//        // Create the input layout
//            hr = g_pd3dDevice->CreateInputLayout( layout, numElements, pVSBlob->GetBufferPointer(),
//                                              pVSBlob->GetBufferSize(), &g_pVertexLayout );
//            pVSBlob->Release();
//            if( FAILED( hr ) )
//            return hr;

//        // Set the input layout
//            g_pImmediateContext->IASetInputLayout( g_pVertexLayout );
//            // Compile the pixel shader
//            ID3DBlob* pPSBlob = NULL;
//        hr = CompileShaderFromFile( L"Tutorial02.fx", "PS", "ps_4_0", &pPSBlob );
//        if( FAILED( hr ) )
//        {
//            MessageBox( NULL,
//                        L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK );
//            return hr;
//        }

//            // Create the pixel shader
//            hr = g_pd3dDevice->CreatePixelShader( pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, &g_pPixelShader );
//            pPSBlob->Release();
//        if( FAILED( hr ) )
//            return hr;

//        // Create vertex buffer
//        SimpleVertex vertices[] =
//        {
//            XMFLOAT3( 0.0f, 0.5f, 0.5f ),
//            XMFLOAT3( 0.5f, -0.5f, 0.5f ),
//            XMFLOAT3( -0.5f, -0.5f, 0.5f ),
//        };
//        D3D11_BUFFER_DESC bd;
//            ZeroMemory( &bd, sizeof(bd) );
//        bd.Usage = D3D11_USAGE_DEFAULT;
//        bd.ByteWidth = sizeof( SimpleVertex ) * 3;
//        bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
//            bd.CPUAccessFlags = 0;
//        D3D11_SUBRESOURCE_DATA InitData;
//            ZeroMemory( &InitData, sizeof(InitData) );
//        InitData.pSysMem = vertices;
//        hr = g_pd3dDevice->CreateBuffer( &bd, &InitData, &g_pVertexBuffer );
//        if( FAILED( hr ) )
//            return hr;

//        // Set vertex buffer
//        UINT stride = sizeof( SimpleVertex );
//        UINT offset = 0;
//        g_pImmediateContext->IASetVertexBuffers( 0, 1, &g_pVertexBuffer, &stride, &offset );

//        // Set primitive topology
//        g_pImmediateContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

//        return S_OK;
//    }

//    void Render()
//    {
//        // Clear the back buffer
//        float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red,green,blue,alpha
//        g_pImmediateContext->ClearRenderTargetView( g_pRenderTargetView, ClearColor );

//        // Render a triangle
//        g_pImmediateContext->VSSetShader( g_pVertexShader, NULL, 0 );
//        g_pImmediateContext->PSSetShader( g_pPixelShader, NULL, 0 );
//        g_pImmediateContext->Draw( 3, 0 );

//        // Present the information rendered to the back buffer to the front buffer (the screen)
//        g_pSwapChain->Present( 0, 0 );
//    }

//};

//    IDXGIFactory1* pFactory(0);
//    HRESULT hr = CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**) &pFactory);

//    if (FAILED(hr))
//    {
//        log.log(stringify(hr));
//    }
//    else
//    {

//        UINT i = 0;
//        IDXGIAdapter1 * pAdapter;
//        while(pFactory->EnumAdapters1(i, &pAdapter) != DXGI_ERROR_NOT_FOUND)
//        {
//            DXGI_ADAPTER_DESC1 desc;
//            HRESULT hr2 = pAdapter->GetDesc1(&desc);
//            if (FAILED(hr2))
//            {
//                log.log(stringify(hr2));
//            }
//            log.log(QString::fromWCharArray(desc.Description));

//            UINT j = 0;
//            IDXGIOutput* pOutput(0);
//            while(pAdapter->EnumOutputs(j, &pOutput) != DXGI_ERROR_NOT_FOUND)
//            {
//                DXGI_OUTPUT_DESC desc2;
//                HRESULT hr3 = pOutput->GetDesc(&desc2);
//                if (FAILED(hr3))
//                {
//                    log.log(stringify(hr3));
//                }

//                log.log(QString::fromWCharArray(desc2.DeviceName));

//                pOutput->Release();
//                j++;
//            }
//            pAdapter->Release();
//            ++i;
//        }
//    }

//    if (pFactory)
//        pFactory->Release();
