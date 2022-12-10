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
    MenuLabel* clubLabel = new StandartLabel("Club");
    MenuLabel* playersLabel = new StandartLabel("Players");
    MenuLabel* coachingStaff = new StandartLabel("Coaches");
    MenuLabel* gamesLabel = new StandartLabel("Matches");
    MenuLabel* tournsLabel = new StandartLabel("Tournaments");
    MenuLabel* goalsLabel = new StandartLabel("Goals");
    MenuLabel* authoLabel = new AuthorizationLabel("Authorization");

    addMenuLabel(clubLabel);
    addMenuLabel(playersLabel);
    addMenuLabel(coachingStaff);
    addMenuLabel(gamesLabel);
    addMenuLabel(tournsLabel);
    addMenuLabel(goalsLabel);
    addMenuLabel(authoLabel);

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
