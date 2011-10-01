#ifndef PIXELSHADER_H
#define PIXELSHADER_H

#include "Global.h"

DeclShared(PixelShader)
class PixelShader : public LogWriter
{
public:
    ~PixelShader();

private:
    friend class Device;
    PixelShader(Log*);
    ID3D11PixelShader* m_pPixelShader;
};

#endif // PIXELSHADER_H
