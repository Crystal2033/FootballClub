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
    label->setAutoFillBackground(true);
    label->setFixedHeight(70);
    label->setFrameStyle(QFrame::WinPanel | QFrame::Raised);
    mainLay = new QVBoxLayout;


}

void MenuLabel::setChosen(const bool chosenStatus)
{
    isChosen = chosenStatus;
}

QString MenuLabel::getText()
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

void MenuLabel::setBaseColor()
{
    labelColor = baseColor;
    label->setFrameStyle(QFrame::WinPanel | QFrame::Raised);
    setBackgroundLabelColor();
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

void MenuLabel::notifyObservers()
{
    for (auto obs : observers) {
        obs->updateByObserver();
    }
}
