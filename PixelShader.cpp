#include "PixelShader.h"

PixelShader::PixelShader(Log* pLog)
    : LogWriter(pLog)
    , m_pPixelShader(0)
{}


PixelShader::~PixelShader()
{
    if (m_pPixelShader)
        m_pPixelShader->Release();
}
