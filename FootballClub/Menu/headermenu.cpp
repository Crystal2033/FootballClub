/***************************************************************************
 *                                                                         *
 *   Copyright (C) 10.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "headermenu.h"

HeaderMenu::HeaderMenu(QWidget *parent)
    : QWidget{parent}
{

}

void HeaderMenu::addMenuLabel(MenuLabel* const& menuLabel)
{
    menuLabels.append(menuLabel);
}
