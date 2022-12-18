/***************************************************************************
 *                                                                         *
 *   Copyright (C) 10.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "menulabel.h"

MenuLabel::MenuLabel(QString labelName, const LABEL_TYPE labelType, QWidget *parent)
    : QWidget{parent}
{
    label = new QLabel(labelName);
    label->setAlignment(Qt::AlignCenter);
    label->setAutoFillBackground(true);
    label->setFixedHeight(70);
    label->setFrameStyle(QFrame::WinPanel | QFrame::Raised);
    this->labelType = labelType;
    mainLay = new QVBoxLayout;
}

void MenuLabel::setChosenAndChangeColor(const bool chosenStatus)
{
    isChosen = chosenStatus;
}


QString MenuLabel::getText() const
{
    return label->text();
}

void MenuLabel::createStyles()
{
    label->setStyleSheet("color: white;"
                         "font-size: 25px;"
                         "font-weight: bold;"
                         );
}

void MenuLabel::setBackgroundLabelColor()
{
    QPalette pal = label->palette();
    pal.setColor(label->backgroundRole(), labelColor);
    label->setPalette(pal);
}

void MenuLabel::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    emit clicked();
}


void MenuLabel::addObserver(InterfaceObserver *observer)
{
    this->observers.append(observer);
}

void MenuLabel::removeObserver(InterfaceObserver *observer)
{
    QList<InterfaceObserver*>::ConstIterator it = observers.constBegin();
    for (; it != observers.constEnd(); ++it) {
        if (*it == observer) {
            observers.erase(it);
            return;
        }
    }
}

void MenuLabel::removeObservers()
{
    observers.clear();
}

bool MenuLabel::getIsChosen() const
{
    return isChosen;
}

LABEL_TYPE MenuLabel::getLabelType() const
{
    return labelType;
}

MenuLabel::~MenuLabel()
{
}

void MenuLabel::notifyObservers(const REQUEST_TYPE requestStatus, BaseNote* note)
{
    for (auto obs : observers) {
        obs->updateByObserver(requestStatus);
    }
}
