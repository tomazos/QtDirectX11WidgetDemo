// (C) 2011, Andrew Tomazos <andrew@tomazos.com>.

#ifndef ILOGRECEIVER_H
#define ILOGRECEIVER_H

#include "Global.h"

class ILogReader
{
public:
    virtual void log(const QString& sMessage) = 0;
};

#endif // ILOGRECEIVER_H
