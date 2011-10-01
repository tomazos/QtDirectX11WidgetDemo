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
