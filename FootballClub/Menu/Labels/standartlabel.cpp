/***************************************************************************
 *                                                                         *
 *   Copyright (C) 10.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "standartlabel.h"

StandartLabel::StandartLabel(const QString labelName, const LABEL_TYPE labelType, QWidget* parent)
    :MenuLabel(labelName, labelType, parent)
{
    createStyles();
    baseColor = QColor("#5287c3");
    labelColor = baseColor;
    setBackgroundLabelColor();
    mainLay->addWidget(label);
    setLayout(mainLay);

    connect(this, &MenuLabel::clicked, this, &StandartLabel::onLabelClicked);
}

void StandartLabel::setChosenAndChangeColor(const bool chosenStatus)
{
    MenuLabel::setChosenAndChangeColor(chosenStatus);

    if(isChosen){
        labelColor = QColor("#0F315B");
        setBackgroundLabelColor();
        label->setFrameStyle(QFrame::WinPanel | QFrame::Sunken);
    }
    else{
        label->setFrameStyle(QFrame::WinPanel | QFrame::Raised);
        labelColor = baseColor;
        setBackgroundLabelColor();
    }
}

void StandartLabel::onLabelClicked()
{
    notifyObservers(SET_FALSE_IN_LABELS);
    setChosenAndChangeColor(true);
    notifyObservers(SEND_CHOSEN_DATA_TYPE);
}




