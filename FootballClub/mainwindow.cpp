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
    //connectToDatabase();
    mainLay = new QVBoxLayout;
    this->centralWidget()->setLayout(mainLay);
    createHeaderMenu();
}

MainWindow::~MainWindow()
{
    delete database;
    delete ui;
}



bool MainWindow::connectToDatabase() //should be called ine time in
{
    if(database != nullptr){
        return false;
    }
    else{
        database = new DataBase;
    }
    return database->createConnection("QPSQL", "FootballClub", "postgres", "gomer2002");
}

void MainWindow::createHeaderMenu()
{
    headerMenu = new HeaderMenu;
    headerMenu->addObserver((InterfaceObserver*)windowManager);
    mainLay->addWidget(headerMenu);
}

