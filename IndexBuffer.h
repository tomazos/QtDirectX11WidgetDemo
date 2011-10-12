// (C) 2011, Andrew Tomazos <andrew@tomazos.com>.

#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

#include "Global.h"

DeclShared(IndexBuffer);
class IndexBuffer : public LogWriter
{
public:
    ~IndexBuffer();

private:
    friend class Device;
    IndexBuffer(Log*);
    ID3D11Buffer* m_pBuffer;
};

#endif // INDEXBUFFER_H
