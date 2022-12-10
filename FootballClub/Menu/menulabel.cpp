/***************************************************************************
 *                                                                         *
 *   Copyright (C) 10.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "menulabel.h"

MenuLabel::MenuLabel(QString labelName, QWidget *parent)
    : QWidget{parent}
{
    label = new QLabel(labelName);
    label->setAlignment(Qt::AlignCenter);
    label->adjustSize();
}

void MenuLabel::setChosen(const bool chosenStatus)
{
    isChosen = chosenStatus;
}

void MenuLabel::createStyles()
{
    label->setStyleSheet("color: white"
                         "font-size: 25px;"
                         "font-weight: bold;"
                         ""
                         "");
}
