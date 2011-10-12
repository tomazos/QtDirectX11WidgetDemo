// (C) 2011, Andrew Tomazos <andrew@tomazos.com>.

#include "VertexShader.h"

VertexShader::VertexShader(Log* pLog)
    : LogWriter(pLog)
    , m_pVertexShader(0)
{}


VertexShader::~VertexShader()
{
    if (m_pVertexShader)
        m_pVertexShader->Release();
}
