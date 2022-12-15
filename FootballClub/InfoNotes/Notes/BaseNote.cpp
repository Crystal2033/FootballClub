/***************************************************************************
 *                                                                         *
 *   Copyright (C) 14.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "BaseNote.h"
BaseNote::BaseNote(QWidget *parent)
    :QWidget(parent)
{
    modifyButton = new QPushButton;
    modifyButton->setFixedSize(75, 55);
    modifyButton->setIconSize(QSize(0.75 * modifyButton->size().width(), 0.75 * modifyButton->size().height()));
    modifyButton->setIcon(QIcon(":/pictures/Pics/modifyData.png"));

    saveChangesButton = new QPushButton("Save changes");
    saveChangesButton->setStyleSheet("background-color: darkgreen;"
                                     "color:white;"
                                     "font-size: 20px;"
                                     "font-wight: bold;"
                                     "");

    cancelSaving = new QPushButton("Cancel modifying");
    cancelSaving->setStyleSheet("background-color: darkred;"
                                "color:white;"
                                "font-size: 20px;"
                                "font-wight: bold;"
                                "");
}

void BaseNote::setNoteViewType(const NOTE_VIEW_TYPE type)
{
    noteViewType = type;
}

NOTE_VIEW_TYPE BaseNote::getNoteViewTytpe() const
{
    return noteViewType;
}

BaseNote::~BaseNote()
{

}


void BaseNote::addObserver(InterfaceObserver *observer)
{
    this->observers.append(observer);
}

void BaseNote::removeObserver(InterfaceObserver *observer)
{
    QList<InterfaceObserver*>::ConstIterator it = observers.constBegin();
    for (; it != observers.constEnd(); ++it) {
        if (*it == observer) {
            observers.erase(it);
            return;
        }
    }
}

void BaseNote::removeObservers()
{
    observers.clear();
}

void BaseNote::notifyObservers(const REQUEST_TYPE requestStatus, BaseNote *note)
{
    for (auto obs : observers) {
        obs->updateByObserver(requestStatus, note);
    }
}

