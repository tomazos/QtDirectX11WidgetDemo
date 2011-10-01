#ifndef WINUTILS_H
#define WINUTILS_H

#include "windows.h"

#include <QtCore/QString>

class WinUtils
{
public:
    static QString WinUtils::stringify(LPTSTR str);
    static QString WinUtils::stringify(HRESULT hresult);
};


class DestringifyLPTSTR
{
public:
    DestringifyLPTSTR(const QString& s)
    #ifdef UNICODE
        : m_s(s)
    {
    }

    #else
        : m_b(s.toAscii())
    {
    }

    #endif

    operator LPTSTR()
    #ifdef UNICODE
    { return (LPTSTR) m_s.utf16(); }
    #else
    { return m_b.data(); }
    #endif

private:

    #ifdef UNICODE
        QString m_s;
    #else
        QByteArray m_b;
    #endif

};

class DestringifyLPCSTR
{
public:
    DestringifyLPCSTR(const QString& s)
        : m_b(s.toAscii())
    {
    }

    operator LPCSTR()
    { return (LPCSTR) m_b.data(); }

private:
    QByteArray m_b;
};

#endif // WINUTILS_H
