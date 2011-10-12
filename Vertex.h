#ifndef VERTEX_H
#define VERTEX_H

class Vertex
{
public:
    Vertex()
        : m_fX(0)
        , m_fY(0)
        , m_fZ(0)
        , m_fR(0)
        , m_fG(0)
        , m_fB(0)
        , m_fA(0)
    {}

    Vertex(float fX, float fY, float fZ, float fR, float fG, float fB, float fA)
        : m_fX(fX)
        , m_fY(fY)
        , m_fZ(fZ)
        , m_fR(fR)
        , m_fG(fG)
        , m_fB(fB)
        , m_fA(fA)
    {}

private:
    float m_fX;
    float m_fY;
    float m_fZ;
    float m_fR;
    float m_fG;
    float m_fB;
    float m_fA;
};

#endif // VERTEX_H
