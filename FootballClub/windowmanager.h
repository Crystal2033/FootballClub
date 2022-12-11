/***************************************************************************
 *                                                                         *
 *   Copyright (C) 11.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H
#pragma once
#include "mainwindow.h"
#include "DataBase/database.h"

class WindowManager : public InterfaceObserver
{
public:
    WindowManager();
    ~WindowManager();
    void show();
private:
    DataBase* database = nullptr;
    MainWindow* window = nullptr;

    bool connectToDatabase();
    void updateByObserver(const REQUEST_TYPE requestStatus) override;

};

#endif // WINDOWMANAGER_H
