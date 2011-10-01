#ifndef LOGWRITER_H
#define LOGWRITER_H

#include "Log.h"

#define INFO(sMessage) LogWriter_info(__FILE__, __LINE__, sMessage)
#define ASSERT(bCondition) { if (!(bCondition)) \
    { LogWriter_info(__FILE__, __LINE__, QString("Assertion Failed").arg(bCondition)); } }

class LogWriter
{
public:
    LogWriter(Log* pLog = 0);

    void setLog(Log* pLog);

protected:
    void LogWriter_info(const QString& sFile, quint64 iLine, const QString& sMessage);

    Log* m_pLog;
};

#endif // LOGWRITER_H
