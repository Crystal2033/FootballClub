/***************************************************************************
 *                                                                         *
 *   Copyright (C) 09.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
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

void MainWindow::updateByObserver(const REQUEST_TYPE requestStatus)
{
    qInfo() << "chosen status is:" << headerMenu->getChosenDataType();
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
    headerMenu->addObserver(this);
    mainLay->addWidget(headerMenu);
}

