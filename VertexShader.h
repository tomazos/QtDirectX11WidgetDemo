// (C) 2011, Andrew Tomazos <andrew@tomazos.com>.

#ifndef VERTEXSHADER_H
#define VERTEXSHADER_H

#include "Global.h"

DeclShared(VertexShader)
class VertexShader : public LogWriter
{
public:
    ~VertexShader();

private:
    friend class Device;
    VertexShader(Log*);
    ID3D11VertexShader* m_pVertexShader;
};

#endif // VERTEXSHADER_H
