// (C) 2011, Andrew Tomazos <andrew@tomazos.com>.

#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include "Global.h"

DeclShared(VertexBuffer);
class VertexBuffer : public LogWriter
{
public:
    ~VertexBuffer();

private:
    friend class Device;
    VertexBuffer(Log*);
    ID3D11Buffer* m_pBuffer;
};

#endif // VERTEXBUFFER_H
