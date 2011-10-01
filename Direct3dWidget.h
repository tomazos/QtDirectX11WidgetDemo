#ifndef DIRECT3DWIDGET_H
#define DIRECT3DWIDGET_H

#include "Global.h"

#include <QtGui/QWidget>

#include "IEngineView.h"

class Direct3dWidget : public QWidget, public LogWriter, public IEngineView
{
    Q_OBJECT
public:
    explicit Direct3dWidget(QWidget *parent = 0);

    virtual HWND EngineView_getHWND() { return winId(); }
    virtual int EngineView_getWidth() { return width(); }
    virtual int EngineView_getHeight() { return height(); }
    virtual void EngineView_setEngine(Engine* pEngine) { m_pEngine = pEngine; }

protected:
    virtual void resizeEvent(QResizeEvent* pEvent);

private:
    Engine* m_pEngine;
};

#endif // DIRECT3DWIDGET_H
