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

    searchLay = new QHBoxLayout;
    //need to add icon
    QIcon searchIcon(":/pictures/Pics/search.png");
    seacrhLabel = new QLabel;
    seacrhLabel->setFixedSize(50, 50);
    seacrhLabel->setPixmap(searchIcon.pixmap(seacrhLabel->size()));
    searchLineEdit = new LineEdit("");
    searchLineEdit->setNewFixedSize(300, 50);

    searchLay->setSpacing(0);
    searchLay->setAlignment(Qt::AlignCenter);
    searchLay->addWidget(seacrhLabel, 0, Qt::AlignHCenter);
    searchLay->addWidget(searchLineEdit, 0, Qt::AlignLeft);


    connect(searchLineEdit, &LineEdit::emitEditingFinished, this, &DataDemonstrator::searchEditingFinished);


    addNoteButton = new QPushButton();
    QIcon addIcon(":/pictures/Pics/addNote.png");
    addNoteButton->setIcon(addIcon);
    addNoteButton->setFixedSize(100, 100);
    addNoteButton->setIconSize(addNoteButton->size());

    addNoteButton->setStyleSheet("QPushButton{"
                                 "border: none;"
                                 "border-radius:15px;"
                                 "}"
                                 "QPushButton:hover{"
                                 "background-color: #212e3c;"
                                 "}"
                                 ""
                                 "");
    connect(addNoteButton, &QPushButton::clicked, this, &DataDemonstrator::onAddNoteButtonClicked);
    layout->addWidget(addNoteButton, 0, Qt::AlignHCenter);
    addNoteButton->setVisible(false);

    layout->addLayout(searchLay);
    layout->setAlignment(Qt::AlignTop);

    scrollArea->setWidgetResizable(true);

    scrollArea->setStyleSheet(""
                              "background-color:#2E4053;"
                              ""
                              "");
    scrollArea->setWidget(this);
    parentLay->setAlignment(Qt::AlignTop);

    parentLay->addWidget(scrollArea);


    logoIcon = QIcon(":/pictures/Pics/psg-icon.png");

}

void DataDemonstrator::showData(const QList<BaseNote*> &notes, const LABEL_TYPE& currDataType)
{
    currShowingDataType = currDataType;
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
    if(clubAndDevInfoLay == nullptr){
        clubAndDevInfoLay = new QVBoxLayout;
        parentLay->addLayout(clubAndDevInfoLay);
    }

    dataOfClubCreation->setStyleSheet("color: white;"
                                      "font-size: 60px;"
                                      "font-weight: bold;"
                                      "");
    developerInfo->setStyleSheet("color: grey;"
                                      "font-size: 20px;"
                                      "font-weight: bold;"
                                      "");

    dataOfClubCreation->setText("PSG created at " + createdDate);
    developerInfo->setText("Developed with soul by Kulikov Pavel.");

    clubAndDevInfoLay->setContentsMargins(0, 100, 0,0);
    clubAndDevInfoLay->addWidget(iconLabel, 0, Qt::AlignCenter);
    clubAndDevInfoLay->addWidget(dataOfClubCreation, 0, Qt::AlignCenter);
    clubAndDevInfoLay->addWidget(developerInfo, 0, Qt::AlignCenter);
    //clubAndDevInfoLay->setSpacing(100);

}

QString DataDemonstrator::getSearchText() const
{
    if(searchLineEdit != nullptr){
        return searchLineEdit->getText();
    }
    return "NullPtr";
}

void DataDemonstrator::clearSearchText()
{
    searchLineEdit->clearField();
}

LABEL_TYPE DataDemonstrator::getCurrShowingData() const
{
    return currShowingDataType;
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
    if(clubAndDevInfoLay != nullptr){
        delete clubAndDevInfoLay;
        clubAndDevInfoLay = nullptr;
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

void DataDemonstrator::searchEditingFinished()
{
    qInfo() << getSearchText();
    notifyObservers(SEND_CHOSEN_DATA_TYPE);
}
