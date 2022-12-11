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

class WindowManager : public InterfaceObserver
{
public:
    WindowManager();
    void show();
private:
    void updateByObserver(const REQUEST_TYPE requestStatus) override;
    MainWindow* window = nullptr;
};

#endif // WINDOWMANAGER_H
