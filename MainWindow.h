// (C) 2011, Andrew Tomazos <andrew@tomazos.com>.

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

#include "LogView.h"

class IEngineView;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

    void setLog(Log* pLog);
    IEngineView* getEngineView();

    void init();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
