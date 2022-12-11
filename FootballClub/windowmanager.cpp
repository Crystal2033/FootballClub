/***************************************************************************
 *                                                                         *
 *   Copyright (C) 11.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "windowmanager.h"

WindowManager::WindowManager()
{
    window = new MainWindow(this);
    window->setStyleSheet("MainWindow{background-color: #30415B}");
    connectToDatabase();
}

WindowManager::~WindowManager()
{
    delete database;
}

void WindowManager::show()
{
    window->show();
}

bool WindowManager::connectToDatabase()
{
    if(database != nullptr){
        return false;
    }
    else{
        database = new DataBase;
    }
    return database->createConnection("QPSQL", "FootballClub", "postgres", "gomer2002");
}

void WindowManager::updateByObserver(const REQUEST_TYPE requestStatus)
{
    qInfo() << "Found: " << this->window->headerMenu->getChosenDataType();
}
