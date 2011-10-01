#ifndef LOG_H
#define LOG_H

#include <QtCore/QString>
#include <QtCore/QSet>

class ILogReader;

class Log
{
public:

    void log(const QString& sMessage);

    void addLogReceiver(ILogReader* pReceiver);
    void delLogReceiver(ILogReader* pReceiver);

private:
    QSet<ILogReader*> m_receivers;
};

#endif // LOG_H
