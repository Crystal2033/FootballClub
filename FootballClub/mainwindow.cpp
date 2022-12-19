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
    logoClubAndHeaderLay = new QHBoxLayout;
    labelForIcon = new QLabel();

    logoIcon = QIcon(":/pictures/Pics/psg-icon.png");

    labelForIcon->setPixmap(logoIcon.pixmap(100, 100));
    logoClubAndHeaderLay->addWidget(labelForIcon, 1, Qt::AlignTop);
    mainLay->addLayout(logoClubAndHeaderLay);
    this->centralWidget()->setLayout(mainLay);
    createHeaderMenu();
    createDataDemonstrator();
    this->setWindowIcon(QIcon(":/pictures/Pics/psg-icon.png"));
    this->setStyleSheet("MainWindow{background:"
                        " qlineargradient( x1:0 y1:0, x2:1 y2:1, stop:0 #04518e, stop:1 #CD4141);"
                        ""//04518e  CD4141
                        "}");


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
    logoClubAndHeaderLay->addWidget(headerMenu, 10, Qt::AlignTop);
}

void MainWindow::createDataDemonstrator()
{
    mainLay->setContentsMargins(20, 10, 20, 10);
    dataDemonstrator = new DataDemonstrator(mainLay);
    dataDemonstrator->addObserver((InterfaceObserver*)windowManager);
}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
        {
            // handle the key press, perhaps giving the item text a default value
        QMessageBox msgBox;
        msgBox.setWindowTitle("Close window");
        msgBox.setText("Are you want close the programm?");
        msgBox.setStyleSheet("background-color:#3d4c78;"
                             "color: white;"
                             "font-size: 20px;"
                             "");
        msgBox.setStandardButtons(QMessageBox::Yes);
        msgBox.addButton(QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);
        if(msgBox.exec() == QMessageBox::Yes){
          this->close();
        }else {

        }

        }
        else
        {
             // call the default implementation
        }
}


