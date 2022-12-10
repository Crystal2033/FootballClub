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
#include "Menu/standartlabel.h"
#include "Menu/authorizationlabel.h"
#include <QWidget>
#include <QList>
#include <QBoxLayout>
#include <PatternObserver/observer.h>

class HeaderMenu : public QWidget, public InterfaceObserver
{
    Q_OBJECT
public:
    explicit HeaderMenu(QWidget *parent = nullptr);
    ~HeaderMenu();
    void updateByObserver();

private:
    QHBoxLayout* horLay = nullptr;
    void createMenu();
    void insertLabelsInLayout();
    void addMenuLabel(MenuLabel* const& menuLabel);
    QList<MenuLabel*> menuLabels;

signals:

};

#endif // HEADERMENU_H
