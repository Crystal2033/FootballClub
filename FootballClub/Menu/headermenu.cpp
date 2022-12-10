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

void HeaderMenu::createMenu()
{
    MenuLabel* clubLabel = new StandartLabel("Club");
    MenuLabel* playersLabel = new StandartLabel("Players");
    MenuLabel* coachingStaff = new StandartLabel("Coaches");
    MenuLabel* gamesLabel = new StandartLabel("Matches");
    MenuLabel* tournsLabel = new StandartLabel("Tournaments");
    MenuLabel* goalsLabel = new StandartLabel("Goals");

    addMenuLabel(clubLabel);
    addMenuLabel(playersLabel);
    addMenuLabel(coachingStaff);
    addMenuLabel(tournsLabel);
    addMenuLabel(goalsLabel);

}

void HeaderMenu::addMenuLabel(MenuLabel* const& menuLabel)
{
    menuLabels.append(menuLabel);
}
