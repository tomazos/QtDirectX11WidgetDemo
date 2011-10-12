// (C) 2011, Andrew Tomazos <andrew@tomazos.com>.

#ifndef LOGVIEW_H
#define LOGVIEW_H

#include <QtCore/QString>

#include <QtGui/QTextEdit>

#include "ILogReader.h"

class Log;

class LogView : public QTextEdit, public ILogReader
{
    Q_OBJECT
public:
    explicit LogView(QWidget *parent = 0);
    ~LogView();

    void log(const QString &sMessage);

    void setLog(Log* pLog);

private:
    Log* m_pLog;
};

#endif // LOGVIEW_H
