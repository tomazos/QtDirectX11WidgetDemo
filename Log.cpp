// (C) 2011, Andrew Tomazos <andrew@tomazos.com>.

#include "Log.h"

#include "ILogReader.h"

void Log::log(const QString& sMessage)
{
    foreach(ILogReader* pReceiver, m_receivers)
    {
        pReceiver->log(sMessage);
    }
}

void Log::addLogReceiver(ILogReader* pReceiver)
{
    m_receivers += pReceiver;
}

void Log::delLogReceiver(ILogReader* pReceiver)
{
    m_receivers -= pReceiver;
}
