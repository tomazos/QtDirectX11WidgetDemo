#include "Texture2d.h"

Texture2d::Texture2d(Log* pLog, ID3D11Texture2D* pTexture)
    : LogWriter(pLog)
    , m_pTexture(pTexture)
{
}

Texture2d::~Texture2d()
{
    if (m_pTexture)
        m_pTexture->Release();
}

int Texture2d::height()
{
    D3D11_TEXTURE2D_DESC s;
    m_pTexture->GetDesc(&s);
    return s.Height;
}

int Texture2d::width()
{
    D3D11_TEXTURE2D_DESC s;
    m_pTexture->GetDesc(&s);
    return s.Width;
}
