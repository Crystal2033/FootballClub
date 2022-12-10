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
    horLay = new QHBoxLayout;
    setLayout(horLay);
    createMenu();
}

HeaderMenu::~HeaderMenu()
{
    for(auto label : menuLabels){
        delete label;
    }
    delete horLay;
}

void HeaderMenu::updateByObserver()
{
    for(auto menuLabel : menuLabels){
        menuLabel->setChosen(false);
        menuLabel->setBaseColor();
    }
}

void HeaderMenu::createMenu()
{//TODO: probably can to do addMenuLabel(new StandartLabel("Club"));


    addMenuLabel(new StandartLabel("Club"));
    addMenuLabel(new StandartLabel("Players"));
    addMenuLabel(new StandartLabel("Coaches"));
    addMenuLabel(new StandartLabel("Matches"));
    addMenuLabel(new StandartLabel("Tournaments"));
    addMenuLabel(new StandartLabel("Goals"));
    addMenuLabel(new AuthorizationLabel("Authorization"));

    insertLabelsInLayout();
}

void HeaderMenu::insertLabelsInLayout()
{
    for(MenuLabel* menuLabel : menuLabels){
        horLay->addWidget(menuLabel);
    }
}

void HeaderMenu::addMenuLabel(MenuLabel* const& menuLabel)
{
    menuLabels.append(menuLabel);
    menuLabel->addObserver(this);
}
