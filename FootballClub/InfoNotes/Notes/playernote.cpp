/***************************************************************************
 *                                                                         *
 *   Copyright (C) 10.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "playernote.h"
#include "InfoNotes/DataWidgets/label.h"

void PlayerNote::extend()
{
    //for future
}

PlayerNote::PlayerNote(QSqlQuery* query, QWidget *parent)
    :BaseNote(parent)
{
    gameNumberLbl = new QLabel("Number");
    gameNumberLbl->setStyleSheet("color: #3A40B0;"
                                 "font-size:10px;"
                                 ""
                                 "");
    playerNameLbl= new QLabel("Name");
    playerNameLbl->setStyleSheet("color: #3A40B0;"
                                 "font-size:10px;"
                                 ""
                                 "");
    posLbl = new QLabel("Position");
    posLbl->setStyleSheet("color: #3A40B0;"
                                 "font-size:10px;"
                                 ""
                                 "");
    birthdayLbl  = new QLabel("Birthday");
    birthdayLbl->setStyleSheet("color: #3A40B0;"
                                 "font-size:10px;"
                                 ""
                                 "");
    heightLbl = new QLabel("Height (m)");
    heightLbl->setStyleSheet("color: #3A40B0;"
                                 "font-size:10px;"
                                 ""
                                 "");
    weightLbl  = new QLabel("Weight (kg)");
    weightLbl->setStyleSheet("color: #3A40B0;"
                                 "font-size:10px;"
                                 ""
                                 "");
    countryLbl= new QLabel("Nationality");
    countryLbl->setStyleSheet("color: #3A40B0;"
                                 "font-size:10px;"
                                 ""
                                 "");
    teamTypeLbl = new QLabel("Team type");
    teamTypeLbl->setStyleSheet("color: #3A40B0;"
                                 "font-size:10px;"
                                 ""
                                 "");
    inClubSinceLbl = new QLabel("Signed at PSG");
    inClubSinceLbl->setStyleSheet("color: #3A40B0;"
                                 "font-size:10px;"
                                 ""
                                 "");
    contractEndsAtLbl = new QLabel("Contract ends at");
    contractEndsAtLbl->setStyleSheet("color: #3A40B0;"
                                 "font-size:10px;"
                                 ""
                                 "");
    salaryLbl = new QLabel("Salary per year ($)");
    salaryLbl->setStyleSheet("color: #3A40B0;"
                                 "font-size:10px;"
                                 ""
                                 "");


    if(query != nullptr){
        QSqlRecord record = query->record();
        recordId = query->value(record.indexOf("id")).toInt();
        name = new Label(query->value(record.indexOf("name")).toString());

        position = new Label(query->value(record.indexOf("pos")).toString()); //Taking one because second teams have to has the same type
        teamType = new Label(query->value(record.indexOf("teamtype")).toString());

        height = new Label(query->value(record.indexOf("height")).toString());
        weight = new Label(query->value(record.indexOf("weight")).toString());
        countryFrom = new Label(query->value(record.indexOf("country")).toString());



        QDateTime dateTimeConverter = QDateTime::fromString(query->value(record.indexOf("birthday")).toString(), "yyyy-MM-dd");
        if(!dateTimeConverter.isValid()){
            birthdayDate = new Label("Bad format date");
        }
        else{
            birthdayDate = new Label(dateTimeConverter.toString("yyyy-MM-dd"));
        }

        salary = new Label(deleteNotNeedSymbolsInSalaryValue(query->value(record.indexOf("yearsalary")).toString()));
        gameNumber = new Label(query->value(record.indexOf("gamenumber")).toString());

        dateTimeConverter = QDateTime::fromString(query->value(record.indexOf("inclubsince")).toString(), "yyyy-MM-dd");
        if(!dateTimeConverter.isValid()){
            sinceInClub = new Label("Bad format date");
        }
        else{
            sinceInClub = new Label(dateTimeConverter.toString("yyyy-MM-dd"));
        }


        dateTimeConverter = QDateTime::fromString(query->value(record.indexOf("leftfromclub")).toString(), "yyyy-MM-dd");
        if(!dateTimeConverter.isValid()){
            contractEndsAt = new Label("Bad format date");
        }
        else{
            contractEndsAt = new Label(dateTimeConverter.toString("yyyy-MM-dd"));
        }

    }
    else{

        name = new Label("");

        position = new Label(""); //Taking one because second teams have to has the same type
        teamType = new Label("");

        height = new Label("0.0");
        weight = new Label("0");
        countryFrom = new Label("");


        QDateTime dateTimeConverter = QDateTime::currentDateTime();
        birthdayDate = new Label(dateTimeConverter.toString("yyyy-MM-dd"));

        salary = new Label("0");
        gameNumber = new Label("1");

        sinceInClub = new Label(dateTimeConverter.toString("yyyy-MM-dd"));
        contractEndsAt = new Label(dateTimeConverter.toString("yyyy-MM-dd"));

    }

    globalLay = new QVBoxLayout;

    playerInfoLay = new QHBoxLayout;
    playerNumberLay = new QVBoxLayout;
    playerNameLay = new QVBoxLayout;
    playerPosLay = new QVBoxLayout;
    personInfoLay = new QHBoxLayout;
    personBirthdayLay = new QVBoxLayout;
    personHeightLay = new QVBoxLayout;
    personWeightLay = new QVBoxLayout;
    personCountryLay = new QVBoxLayout;
    clubInfoLay = new QHBoxLayout;
    clubInfoTeamTypeLay = new QVBoxLayout;
    clubInfoSinceLay = new QVBoxLayout;
    clubInfoLeftAtLay = new QVBoxLayout;
    salaryLay = new QVBoxLayout;

    playerInfoLay->addLayout(playerNumberLay);
    playerInfoLay->addLayout(playerNameLay);
    playerInfoLay->addLayout(playerPosLay);
    personInfoLay->addLayout(personBirthdayLay);
    personInfoLay->addLayout(personHeightLay);
    personInfoLay->addLayout(personWeightLay);
    personInfoLay->addLayout(personCountryLay);
    clubInfoLay->addLayout(clubInfoTeamTypeLay);
    clubInfoLay->addLayout(clubInfoSinceLay);
    clubInfoLay->addLayout(clubInfoLeftAtLay);


    modifyButtonsLay = new QHBoxLayout;
    deleteNoteButtonLay = new QHBoxLayout;

    setAllDataOnLayout();

    deleteNoteButtonLay->addWidget(deleteNoteButton, 0, Qt::AlignRight);
    modifyButtonsLay->addWidget(cancelSaving, 0, Qt::AlignCenter);
    cancelSaving->setVisible(false);
    modifyButtonsLay->addWidget(saveChangesButton, 0, Qt::AlignCenter);
    saveChangesButton->setVisible(false);
    modifyButtonsLay->addWidget(modifyButton, 0, Qt::AlignRight);

    globalLay->addLayout(deleteNoteButtonLay);
    globalLay->addLayout(playerInfoLay);
    globalLay->addLayout(personInfoLay);
    globalLay->addLayout(clubInfoLay);
    globalLay->addLayout(salaryLay);
    globalLay->addLayout(modifyButtonsLay);

    setLayout(globalLay);

    connect(modifyButton, &QPushButton::clicked, this, &PlayerNote::modifyNoteView);
    connect(saveChangesButton, &QPushButton::clicked, this, &PlayerNote::onSaveChangesClicked);
    connect(cancelSaving, &QPushButton::clicked, this, &PlayerNote::onCancelModifyingClicked);
    connect(deleteNoteButton, &QPushButton::clicked, this, &PlayerNote::onDeleteButtonClicked);

    setStyles();
}

void PlayerNote::setAllDataOnLayout()
{

    playerNumberLay->addWidget(gameNumberLbl, 0, Qt::AlignCenter);
    playerNumberLay->addWidget(gameNumber, 0, Qt::AlignCenter);

    playerNameLay->addWidget(playerNameLbl, 0, Qt::AlignCenter);
    playerNameLay->addWidget(name, 0, Qt::AlignCenter);

    playerPosLay->addWidget(posLbl, 0, Qt::AlignCenter);
    playerPosLay->addWidget(position, 0, Qt::AlignCenter);

    personBirthdayLay->addWidget(birthdayLbl, 0, Qt::AlignCenter);
    personBirthdayLay->addWidget(birthdayDate, 0, Qt::AlignCenter);

    personHeightLay->addWidget(heightLbl, 0, Qt::AlignCenter);
    personHeightLay->addWidget(height, 0, Qt::AlignCenter);

    personWeightLay->addWidget(weightLbl, 0, Qt::AlignCenter);
    personWeightLay->addWidget(weight, 0, Qt::AlignCenter);

    personCountryLay->addWidget(countryLbl, 0, Qt::AlignCenter);
    personCountryLay->addWidget(countryFrom, 0, Qt::AlignCenter);

    clubInfoTeamTypeLay->addWidget(teamTypeLbl, 0, Qt::AlignCenter);
    clubInfoTeamTypeLay->addWidget(teamType, 0, Qt::AlignCenter);

    clubInfoSinceLay->addWidget(inClubSinceLbl, 0, Qt::AlignCenter);
    clubInfoSinceLay->addWidget(sinceInClub, 0, Qt::AlignCenter);

    clubInfoLeftAtLay->addWidget(contractEndsAtLbl, 0, Qt::AlignCenter);
    clubInfoLeftAtLay->addWidget(contractEndsAt, 0, Qt::AlignCenter);

    salaryLay->addWidget(salaryLbl, 0, Qt::AlignCenter);
    salaryLay->addWidget(salary, 0, Qt::AlignCenter);
}

void PlayerNote::setTournamentComboList(QSqlQuery &query)
{

}

void PlayerNote::setStagesComboList(QSqlQuery &query)
{

}

void PlayerNote::setTeamTypesComboList(QSqlQuery &query)
{

}

void PlayerNote::setClubsComboList(QSqlQuery &query)
{

}

void PlayerNote::setStadiumsComboList(QSqlQuery &query)
{

}

void PlayerNote::setNoteViewType(const NOTE_VIEW_TYPE type)
{

}

void PlayerNote::setStyles()
{

}

void PlayerNote::insertFieldsInMap()
{
    fieldsMap.clear();
    fieldsMap.insert(std::make_pair("gamenumber", gameNumber));
    fieldsMap.insert(std::make_pair("name", name));
    fieldsMap.insert(std::make_pair("pos", position));
    fieldsMap.insert(std::make_pair("birthday", birthdayDate));
    fieldsMap.insert(std::make_pair("weight", weight));
    fieldsMap.insert(std::make_pair("height", height));
    fieldsMap.insert(std::make_pair("country", countryFrom));
    fieldsMap.insert(std::make_pair("teamtype", teamType));
    fieldsMap.insert(std::make_pair("inclubsince", sinceInClub));
    fieldsMap.insert(std::make_pair("leftfromclub", contractEndsAt));
    fieldsMap.insert(std::make_pair("yearsalary", salary));
}

void PlayerNote::saveDataBeforeAction()
{

}

QString PlayerNote::deleteNotNeedSymbolsInSalaryValue(QString salaryValue) const
{
    return salaryValue.replace("?", "");
}

void PlayerNote::modifyNoteView()
{

}

void PlayerNote::onSaveChangesClicked()
{

}

void PlayerNote::onCancelModifyingClicked()
{

}

void PlayerNote::onDeleteButtonClicked()
{

}


