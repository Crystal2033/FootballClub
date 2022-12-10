/***************************************************************************
 *                                                                         *
 *   Copyright (C) 10.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "standartlabel.h"

StandartLabel::StandartLabel(const QString labelName, QWidget* parent)
    :MenuLabel(labelName, parent)
{
    createStyles();
    baseColor = QColor("#6A92CE");
    labelColor = baseColor;
    setBackgroundLabelColor();
    mainLay->addWidget(label);
    setLayout(mainLay);

    connect(this, &MenuLabel::clicked, this, &StandartLabel::onLabelClicked);
}

void StandartLabel::onLabelClicked()
{
    notifyObservers();
    isChosen = true;
    labelColor = QColor("#0F315B");
    setBackgroundLabelColor();
    label->setFrameStyle(QFrame::WinPanel | QFrame::Sunken);
}




