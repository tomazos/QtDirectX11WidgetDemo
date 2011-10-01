#include "WinUtils.h"

QString WinUtils::stringify(LPTSTR str)
{
#ifdef UNICODE
        return QString::fromUtf16(str);
#else
        return QString::fromLatin1(str);
#endif
}

QString WinUtils::stringify(HRESULT hresult)
{
    QString result;

    LPTSTR errorText = NULL;

    FormatMessage( FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        hresult,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&errorText,
        0,
        NULL);

    if ( NULL != errorText )
    {
        result = stringify(errorText);
        LocalFree(errorText);
        errorText = NULL;
    }

    return result;
}
