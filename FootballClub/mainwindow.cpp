/***************************************************************************
 *                                                                         *
 *   Copyright (C) 09.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(WindowManager* manager, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    windowManager = manager;
    ui->setupUi(this);
    mainLay = new QVBoxLayout;
    this->centralWidget()->setLayout(mainLay);
    createHeaderMenu();
    createDataDemonstrator();
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::createHeaderMenu()
{
    headerMenu = new HeaderMenu;
    headerMenu->addObserver((InterfaceObserver*)windowManager);
    mainLay->addWidget(headerMenu, 0, Qt::AlignTop);
}

void MainWindow::createDataDemonstrator()
{
    dataDemonstrator = new DataDemonstrator(mainLay);

}

