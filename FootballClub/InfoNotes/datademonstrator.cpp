/***************************************************************************
 *                                                                         *
 *   Copyright (C) 11.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "datademonstrator.h"
#include <QPushButton>
#include "InfoNotes/Notes/BaseNote.h"

DataDemonstrator::DataDemonstrator(QBoxLayout* parentLay, QWidget *parent)
    : QWidget{parent}
{
    layout = new QVBoxLayout;
    layout->setSpacing(75);
    scrollArea = new QScrollArea();
    scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    this->setLayout(layout);


    scrollArea->setWidgetResizable(true);

    scrollArea->setStyleSheet(""
                              "background-color: #008B8B;"
                              ""
                              "");
    scrollArea->setWidget(this);
    parentLay->setAlignment(Qt::AlignTop);

    parentLay->addWidget(scrollArea);

}

void DataDemonstrator::showData(const QList<BaseNote*> &notes, const LABEL_TYPE dataType)
{
    if(addNoteButton != nullptr){
        delete addNoteButton;
    }
    addNoteButton = new QPushButton("Add");
    addNoteButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    addNoteButton->setStyleSheet("background-color: #33683D;"
                                 "color: white;"
                                 "font-size: 25px;"
                                 "font-weight: bold;"
                                 "");

    layout->addWidget(addNoteButton, Qt::AlignTop);
    connectAddButtonToSlot(dataType);
    deleteDataFromList();

    listOfNotes = notes;
    for(unsigned i = 0; i < listOfNotes.size(); i++){
        layout->addWidget((QWidget*)listOfNotes[i]);
        listOfNotes[i]->show();
    }
}

void DataDemonstrator::setVisibleScrollArea(const bool visibility)
{
    scrollArea->setVisible(visibility);
}

QList<BaseNote *> DataDemonstrator::getListOfNotes() const
{
    return listOfNotes;
}

void DataDemonstrator::deleteDataFromList()
{
    for(unsigned i = 0; i < listOfNotes.size(); i++){
        delete listOfNotes[i];
    }
    listOfNotes.clear();
}

void DataDemonstrator::connectAddButtonToSlot(const LABEL_TYPE dataType)
{
    switch (dataType) {
    case PLAYERS:
        break;
    case COACHES:
        break;
    case MATCHES:
        break;
    case GOALS:
        break;
    case CLUB:
        break;
    case TEAMS:
        break;
    case AUTHO:

        break;

    default:
        break;
    }
}
