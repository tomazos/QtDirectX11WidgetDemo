#include "LogView.h"

LogView::LogView(QWidget *parent)
    : QTextEdit(parent)
    , m_pLog(0)
{
}

LogView::~LogView()
{
    if (m_pLog)
        m_pLog->delLogReceiver(this);
}

void LogView::setLog(Log* pLog)
{
    if (m_pLog)
        m_pLog->delLogReceiver(this);

    m_pLog = pLog;

    if (m_pLog)
        m_pLog->addLogReceiver(this);
}

void LogView::log(const QString &sMessage)
{
    append(sMessage);
}
