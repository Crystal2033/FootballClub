/***************************************************************************
 *                                                                         *
 *   Copyright (C) 10.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "authorizationlabel.h"

#include <QIcon>

AuthorizationLabel::AuthorizationLabel(const QString labelName, const LABEL_TYPE labelType, QWidget* parent):
    MenuLabel("", labelType, parent)
{
    createStyles();
    baseColor = QColor("#52637E");
    labelColor = baseColor;

    setBackgroundLabelColor();
    mainLay->addWidget(label);
    currentIcon = QIcon(":/pictures/Pics/user.png");
    label->setPixmap(currentIcon.pixmap(label->size().width() - 10, label->size().height() - 10));

    setLayout(mainLay);

    connect(this, &MenuLabel::clicked, this, &AuthorizationLabel::onLabelClicked);
}

void AuthorizationLabel::setChosenAndChangeColor(const bool chosenStatus)
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

void AuthorizationLabel::setIsAdmin(const bool isAdmin)
{
    this->isAdmin = isAdmin;
    if(isAdmin){
        currentIcon = QIcon(":/pictures/Pics/userChosen.png");
        label->setPixmap(currentIcon.pixmap(label->size().width() - 10, label->size().height() - 10));
    }
    else{
        currentIcon = QIcon(":/pictures/Pics/user.png");
        label->setPixmap(currentIcon.pixmap(label->size().width() - 10, label->size().height() - 10));
    }
}

void AuthorizationLabel::onLabelClicked()
{
    notifyObservers(SET_FALSE_IN_LABELS);
    setChosenAndChangeColor(true);
    notifyObservers(SEND_CHOSEN_DATA_TYPE);
}



