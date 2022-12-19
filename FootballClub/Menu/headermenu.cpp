/***************************************************************************
 *                                                                         *
 *   Copyright (C) 10.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "headermenu.h"
#include "Labels/standartlabel.h"
#include "Labels/authorizationlabel.h"

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

void HeaderMenu::updateByObserver(const REQUEST_TYPE requestStatus, BaseNote* note)
{
    if(requestStatus == SET_FALSE_IN_LABELS){
        for(auto menuLabel : menuLabels){
            menuLabel->setChosenAndChangeColor(false);
        }
    }
    else if(requestStatus == SEND_CHOSEN_DATA_TYPE){
        for(auto menuLabel : menuLabels){
            if(menuLabel->getIsChosen()){
                chosenDataType = menuLabel->getLabelType();
                break;
            }
        }
        notifyObservers(requestStatus); //Notify WindowManager
    }



}

void HeaderMenu::addObserver(InterfaceObserver *observer)
{
    observers.append(observer);
}

void HeaderMenu::removeObserver(InterfaceObserver *observer)
{
    QList<InterfaceObserver*>::ConstIterator it = observers.constBegin();
    for (; it != observers.constEnd(); ++it) {
        if (*it == observer) {
            observers.erase(it);
            return;
        }
    }
}

void HeaderMenu::removeObservers()
{
    observers.clear();
}

LABEL_TYPE HeaderMenu::getChosenDataType() const
{
    return chosenDataType;
}

void HeaderMenu::createMenu()
{
    addMenuLabel(new StandartLabel("Club", CLUB));
    //addMenuLabel(new StandartLabel("Teams", TEAMS));
    addMenuLabel(new StandartLabel("Players", PLAYERS));
    addMenuLabel(new StandartLabel("Coaches", COACHES));
    addMenuLabel(new StandartLabel("Matches", MATCHES));
    //addMenuLabel(new StandartLabel("Goals", GOALS));
    //addMenuLabel(new AuthorizationLabel("Authorization", AUTHO));

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

void HeaderMenu::notifyObservers(const REQUEST_TYPE requestStatus, BaseNote* note)
{
    Q_UNUSED(note);
    for (auto obs : observers) {
        obs->updateByObserver(requestStatus);
    }
}
