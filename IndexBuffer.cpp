// (C) 2011, Andrew Tomazos <andrew@tomazos.com>.

#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(Log* pLog)
    : LogWriter(pLog)
    , m_pBuffer(0)
{
}

IndexBuffer::~IndexBuffer()
{
    if (m_pBuffer)
        m_pBuffer->Release();
}
