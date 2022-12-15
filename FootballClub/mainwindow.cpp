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
    this->setWindowIcon(QIcon(":/pictures/Pics/psg-icon.png"));
    this->setStyleSheet("MainWindow{background: qlineargradient( x1:0 y1:0, x2:1 y2:1, stop:0 #355471, stop:1 #1D91AD);}");


    this->setWindowTitle("PSG DataBase");
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
    mainLay->setContentsMargins(20, 10, 20, 10);
    dataDemonstrator = new DataDemonstrator(mainLay);

}

