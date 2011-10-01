#ifndef VERTEX_H
#define VERTEX_H

class Vertex
{
public:
    Vertex()
        : m_fX(0)
        , m_fY(0)
        , m_fZ(0)
    {}

    Vertex(float fX, float fY, float fZ)
        : m_fX(fX)
        , m_fY(fY)
        , m_fZ(fZ)
    {}

private:
    float m_fX;
    float m_fY;
    float m_fZ;
};

#endif // VERTEX_H
