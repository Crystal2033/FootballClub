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
}

void WindowManager::show()
{
    window->show();
}

void WindowManager::updateByObserver(const REQUEST_TYPE requestStatus)
{
    qInfo() << "Found: " << this->window->headerMenu->getChosenDataType();
}
