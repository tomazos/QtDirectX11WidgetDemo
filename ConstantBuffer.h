#ifndef CONSTANTBUFFER_H
#define CONSTANTBUFFER_H

#include "Global.h"

DeclShared(ConstantBuffer);
class ConstantBuffer : public LogWriter
{
public:
    ~ConstantBuffer();

private:
    friend class Device;
    ConstantBuffer(Log*, int iNumBytes);
    ID3D11Buffer* m_pBuffer;
    int m_iNumBytes;
};

#endif // CONSTANTBUFFER_H
