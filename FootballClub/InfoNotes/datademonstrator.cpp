/***************************************************************************
 *                                                                         *
 *   Copyright (C) 11.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "datademonstrator.h"
#include <QPushButton>
#include "Enums/Enums.h"
#include "InfoNotes/Notes/BaseNote.h"
#include "WindowManager/windowmanager.h"

DataDemonstrator::DataDemonstrator(QBoxLayout* parentLay, QWidget *parent)
    : QWidget{parent}
{
    this->parentLay = parentLay;
    layout = new QVBoxLayout;
    layout->setSpacing(75);

    scrollArea = new QScrollArea();
    scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    this->setLayout(layout);
    addNoteButton = new QPushButton("Add");
    addNoteButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    addNoteButton->setStyleSheet("background-color: #33683D;"
                                 "color: white;"
                                 "font-size: 25px;"
                                 "font-weight: bold;"
                                 "");
    connect(addNoteButton, &QPushButton::clicked, this, &DataDemonstrator::onAddNoteButtonClicked);
    layout->addWidget(addNoteButton, Qt::AlignTop);
    addNoteButton->setVisible(false);

    scrollArea->setWidgetResizable(true);

    scrollArea->setStyleSheet(""
                              "background-color: #7C98B1;"//008B8B
                              ""
                              "");
    scrollArea->setWidget(this);
    parentLay->setAlignment(Qt::AlignTop);

    parentLay->addWidget(scrollArea);

    clubAndDevInfoLay = new QVBoxLayout;
    parentLay->addLayout(clubAndDevInfoLay);
    logoIcon = QIcon(":/pictures/Pics/psg-icon.png");

}

void DataDemonstrator::showData(const QList<BaseNote*> &notes)
{
    deleteClubAndDevInfo();

    addNoteButton->setVisible(true);
    deleteDataFromListIfNotNeed(notes);

    listOfNotes = notes;
    for(unsigned i = 0; i < listOfNotes.size(); i++){
        layout->addWidget((QWidget*)listOfNotes[i], 0, Qt::AlignTop);
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

void DataDemonstrator::deleteDataFromListIfNotNeed(const QList<BaseNote*>& newNotes)
{
    bool foundedSameNote = false;
    for(unsigned i = 0; i < listOfNotes.size(); i++){ //omg... O(n^2)

        for(unsigned j = 0; j < newNotes.size(); j++){
            if(listOfNotes[i] == newNotes[j]){ //if addresses of ojects are equal
                foundedSameNote = true;
                break;
            }
        }
        if(foundedSameNote){
            foundedSameNote = false;
            continue;
        }
        if(listOfNotes[i] != nullptr){
            delete listOfNotes[i];
        }

    }
    listOfNotes.clear();
}

void DataDemonstrator::addObserver(InterfaceObserver *observer)
{
    this->observers.append(observer);
}

void DataDemonstrator::removeObserver(InterfaceObserver *observer)
{
    QList<InterfaceObserver*>::ConstIterator it = observers.constBegin();
    for (; it != observers.constEnd(); ++it) {
        if (*it == observer) {
            observers.erase(it);
            return;
        }
    }
}

void DataDemonstrator::removeObservers()
{
    observers.clear();
}

void DataDemonstrator::deleteNoteFromList(const BaseNote* note)
{
    for (unsigned i = 0; i < listOfNotes.size(); i++){
        if(listOfNotes[i] == note){
            listOfNotes.remove(i);
        }
    }
}

void DataDemonstrator::showClubData(const QString &createdDate)
{
    if(dataOfClubCreation == nullptr){
        dataOfClubCreation = new QLabel();
        qInfo() << "created date is:" << createdDate;
    }
    if(developerInfo == nullptr){
        developerInfo = new QLabel();
        qInfo() << "developer info is:";
    }
    if(iconLabel == nullptr){
        iconLabel = new QLabel();
        iconLabel->setPixmap(logoIcon.pixmap(iconLabel->size()));
    }
    //clubAndDevInfoLay->setContentsMargins(width()/4, height()/4, width()/4, height()/4);
    dataOfClubCreation->setStyleSheet("color: white;"
                                      "font-size: 60px;"
                                      "font-weight: bold;"
                                      "");
    developerInfo->setStyleSheet("color: grey;"
                                      "font-size: 20px;"
                                      "font-weight: bold;"
                                      "");

    dataOfClubCreation->setText("PSG created at " + createdDate);
    developerInfo->setText("Developed with love by Kulikov Pavel.");

    clubAndDevInfoLay->addWidget(iconLabel, 0, Qt::AlignCenter);
    clubAndDevInfoLay->addWidget(dataOfClubCreation, 0, Qt::AlignCenter);
    clubAndDevInfoLay->addWidget(developerInfo, 0, Qt::AlignCenter);
    clubAndDevInfoLay->setSpacing(100);

}


void DataDemonstrator::deleteClubAndDevInfo()
{
    if(dataOfClubCreation != nullptr){
        delete dataOfClubCreation;
        dataOfClubCreation = nullptr;
    }
    if(developerInfo != nullptr){
        delete developerInfo;
        developerInfo = nullptr;
    }
    if(iconLabel != nullptr){
        delete iconLabel;
        iconLabel = nullptr;
    }
}

void DataDemonstrator::notifyObservers(const REQUEST_TYPE requestStatus, BaseNote *note)
{
    for (auto obs : observers) {
        obs->updateByObserver(requestStatus, note);
    }
}

void DataDemonstrator::onAddNoteButtonClicked()
{
    notifyObservers(ADD_NEW_NOTE);
}
