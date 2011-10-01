#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(Log* pLog)
    : LogWriter(pLog)
    , m_pBuffer(0)
{
}

VertexBuffer::~VertexBuffer()
{
    if (m_pBuffer)
        m_pBuffer->Release();
}
