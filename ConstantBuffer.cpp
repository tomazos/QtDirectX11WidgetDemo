// (C) 2011, Andrew Tomazos <andrew@tomazos.com>.

#include "ConstantBuffer.h"

ConstantBuffer::ConstantBuffer(Log* pLog, int iNumBytes)
    : LogWriter(pLog)
    , m_pBuffer(0)
    , m_iNumBytes(iNumBytes)
{
}

ConstantBuffer::~ConstantBuffer()
{
    if (m_pBuffer)
        m_pBuffer->Release();
}
