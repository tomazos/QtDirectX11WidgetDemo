// (C) 2011, Andrew Tomazos <andrew@tomazos.com>.

#include "LogWriter.h"

LogWriter::LogWriter(Log* pLog)
    : m_pLog(pLog)
{

}

void LogWriter::setLog(Log* pLog)
{
    m_pLog = pLog;
}

void LogWriter::LogWriter_info(const QString& sFile, quint64 iLine, const QString& sMessage)
{
    m_pLog->log(QString("%1:%2:%3").arg(sFile).arg(iLine).arg(sMessage));
}
