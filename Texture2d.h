// (C) 2011, Andrew Tomazos <andrew@tomazos.com>.

#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include "Global.h"

DeclShared(Texture2d)
class Texture2d : public LogWriter
{
public:
    ~Texture2d();

    int height();
    int width();

private:
    friend class SwapChain;
    friend class Device;
    Texture2d(Log*, ID3D11Texture2D*);
    ID3D11Texture2D* m_pTexture;
};

#endif // TEXTURE2D_H
