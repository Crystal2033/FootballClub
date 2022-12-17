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
    if(query != nullptr){
        QSqlRecord record = query->record();
        recordId = query->value(record.indexOf("id")).toInt();
        name = new Label(query->value(record.indexOf("name")).toString());

        position = new Label(query->value(record.indexOf("pos")).toString()); //Taking one because second teams have to has the same type
        teamType = new Label(query->value(record.indexOf("teamtype")).toString());

        height = new Label(query->value(record.indexOf("height")).toString());
        weight = new Label(query->value(record.indexOf("weight")).toString());
        countryFrom = new Label(query->value(record.indexOf("country")).toString());



        QDateTime dateTimeConverter = QDateTime::fromString(query->value(record.indexOf("birthdate")).toString(), "yyyy-MM-dd");
        if(!dateTimeConverter.isValid()){
            birthdayDate = new Label("Bad format date");
        }
        else{
            birthdayDate = new Label(dateTimeConverter.toString("yyyy-MM-dd"));
        }

        salary = new Label(query->value(record.indexOf("yearsalary")).toString());
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
    personInfoLay = new QHBoxLayout;
    personBirthdayLay = new QVBoxLayout;
    personHeightLay = new QVBoxLayout;
    personWeightLay = new QVBoxLayout;
    personCountryLay = new QVBoxLayout;
    clubInfoLay = new QHBoxLayout;
    clubInfoTeamTypeLay = new QVBoxLayout;
    clubInfoSinceLay = new QVBoxLayout;
    clubInfoLeftAtLay = new QVBoxLayout;
    salaryLay = new QHBoxLayout;

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
    QLabel* gameNumberLbl = new QLabel("Number");
    gameNumberLbl->setStyleSheet("color: #3A40B0;"
                                 "font-size:10px;"
                                 ""
                                 "");
    playerNumberLay->addWidget(gameNumberLbl, 0, Qt::AlignCenter);
    playerNumberLay->addWidget(gameNumber, 0, Qt::AlignCenter);
    playerInfoLay->addLayout(playerNumberLay);

    QLabel* playerNameLbl = new QLabel("Name");
    playerNameLbl->setStyleSheet("color: #3A40B0;"
                                 "font-size:10px;"
                                 ""
                                 "");
    playerNameLay->addWidget(playerNameLbl, 0, Qt::AlignCenter);
    playerNameLay->addWidget(name, 0, Qt::AlignCenter);

    playerInfoLay->addLayout(playerNameLay);

    playerInfoLay->addWidget(position, 0, Qt::AlignCenter);

    QLabel* birthdayLbl = new QLabel("Name");
    birthdayLbl->setStyleSheet("color: #3A40B0;"
                                 "font-size:10px;"
                                 ""
                                 "");
    personBirthdayLay->addWidget(birthdayLbl, 0, Qt::AlignCenter);
    personBirthdayLay->addWidget(birthdayDate);
    personInfoLay->addLayout(personBirthdayLay);

    QLabel* heightLbl = new QLabel("Height (m)");
    heightLbl->setStyleSheet("color: #3A40B0;"
                                 "font-size:10px;"
                                 ""
                                 "");
    personHeightLay->addWidget(heightLbl, 0, Qt::AlignCenter);
    personHeightLay->addWidget(height, 0, Qt::AlignCenter);
    personInfoLay->addLayout(personHeightLay);

    QLabel* weightLbl = new QLabel("Weight (kg)");
    weightLbl->setStyleSheet("color: #3A40B0;"
                                 "font-size:10px;"
                                 ""
                                 "");
    personWeightLay->addWidget(weightLbl, 0, Qt::AlignCenter);
    personWeightLay->addWidget(weight, 0, Qt::AlignCenter);
    personInfoLay->addLayout(personWeightLay);

    QLabel* countryLbl = new QLabel("Nationality");
    countryLbl->setStyleSheet("color: #3A40B0;"
                                 "font-size:10px;"
                                 ""
                                 "");
    personCountryLay->addWidget(countryLbl, 0, Qt::AlignCenter);
    personCountryLay->addWidget(countryFrom, 0, Qt::AlignCenter);
    personInfoLay->addLayout(personCountryLay);

    QLabel* teamTypeLbl = new QLabel("Team type");
    teamTypeLbl->setStyleSheet("color: #3A40B0;"
                                 "font-size:10px;"
                                 ""
                                 "");
    clubInfoTeamTypeLay->addWidget(teamTypeLbl, 0, Qt::AlignCenter);
    clubInfoTeamTypeLay->addWidget(teamType, 0, Qt::AlignCenter);
    clubInfoLay->addLayout(clubInfoTeamTypeLay);

    QLabel* inClubSinceLbl = new QLabel("Signed at PSG");
    inClubSinceLbl->setStyleSheet("color: #3A40B0;"
                                 "font-size:10px;"
                                 ""
                                 "");
    clubInfoSinceLay->addWidget(inClubSinceLbl, 0, Qt::AlignCenter);
    clubInfoSinceLay->addWidget(sinceInClub, 0, Qt::AlignCenter);
    clubInfoLay->addLayout(clubInfoSinceLay);

    QLabel* contractEndsAtLbl = new QLabel("Contract ends at");
    contractEndsAtLbl->setStyleSheet("color: #3A40B0;"
                                 "font-size:10px;"
                                 ""
                                 "");
    clubInfoSinceLay->addWidget(contractEndsAtLbl, 0, Qt::AlignCenter);
    clubInfoSinceLay->addWidget(contractEndsAt, 0, Qt::AlignCenter);
    clubInfoLay->addLayout(clubInfoSinceLay);


    QLabel* salaryLbl = new QLabel("Salary per year");
    salaryLbl->setStyleSheet("color: #3A40B0;"
                                 "font-size:10px;"
                                 ""
                                 "");
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
    fieldsMap.insert(std::make_pair("stadium", gameNumber));
    fieldsMap.insert(std::make_pair("club1", name));
    fieldsMap.insert(std::make_pair("club2", position));
    fieldsMap.insert(std::make_pair("teamtype", birthdayDate));
    fieldsMap.insert(std::make_pair("finalscore", height));
    fieldsMap.insert(std::make_pair("stage", countryFrom));
    fieldsMap.insert(std::make_pair("gameDate", teamType));
    fieldsMap.insert(std::make_pair("tournament", sinceInClub));
    fieldsMap.insert(std::make_pair("gameDate", contractEndsAt));
    fieldsMap.insert(std::make_pair("tournament", contractEndsAt));
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


