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
    layout->setSpacing(50);
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

void DataDemonstrator::showData(const QList<BaseNote*> &notes)
{
    deleteDataFromList();

    listOfNotes = notes;
    for(unsigned i = 0; i < listOfNotes.size(); i++){
        layout->addWidget((QWidget*)listOfNotes[i]);
        listOfNotes[i]->show();
    }
}

void DataDemonstrator::deleteDataFromList()
{
    for(unsigned i = 0; i < listOfNotes.size(); i++){
        delete listOfNotes[i];
    }
    listOfNotes.clear();
}
