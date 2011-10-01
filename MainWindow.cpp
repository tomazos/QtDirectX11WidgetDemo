#include "MainWindow.h"

#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setLog(Log* pLog)
{
    ui->logView->setLog(pLog);
    ui->d3dWidget->setLog(pLog);
}

void MainWindow::init()
{
//    ui->d3dWidget->init();
}

IEngineView* MainWindow::getEngineView()
{
    return ui->d3dWidget;
}
