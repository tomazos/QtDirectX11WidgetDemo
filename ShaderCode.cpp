// (C) 2011, Andrew Tomazos <andrew@tomazos.com>.

#include "ShaderCode.h"

PShaderCode ShaderCode::compile(Log* pLog, const QString& sFilename, const QString& sEntryPoint, const QString& sShaderModel)
{
    PShaderCode pShader(new ShaderCode(pLog));

    if (pShader->init(sFilename, sEntryPoint, sShaderModel))
        return pShader;
    else
        return PShaderCode(0);
}

ShaderCode::ShaderCode(Log* pLog)
    : LogWriter(pLog)
    , m_pShaderCode(0)
    , m_pError(0)
{}

bool ShaderCode::init(const QString& sFilename, const QString& sEntryPoint, const QString& sShaderModel)
{
    HRESULT hr = D3DX11CompileFromFile( DestringifyLPTSTR(sFilename), NULL, NULL, DestringifyLPCSTR(sEntryPoint), DestringifyLPCSTR(sShaderModel),
        D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG, 0, NULL, &m_pShaderCode, &m_pError, NULL );

    if( SUCCEEDED(hr) )
    {
        return true;
    }
    else
    {
        INFO(WinUtils::stringify(hr));
        if (m_pError)
            INFO((char*)m_pError->GetBufferPointer());
        return false;
    }
}

ShaderCode::~ShaderCode()
{
    if (m_pShaderCode)
        m_pShaderCode->Release();

    if (m_pError)
        m_pError->Release();
}
