/***************************************************************************
 *                                                                         *
 *   Copyright (C) 10.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef HEADERMENU_H
#define HEADERMENU_H

#include "Menu/menulabel.h"
#include <QWidget>
#include <QList>

class HeaderMenu : public QWidget
{
    Q_OBJECT
public:
    explicit HeaderMenu(QWidget *parent = nullptr);


private:
    void createMenu();
    void addMenuLabel(MenuLabel* const& menuLabel);
    QList<MenuLabel*> menuLabels;

signals:

};

#endif // HEADERMENU_H
