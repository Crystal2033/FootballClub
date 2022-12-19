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
    gameNumberLbl->setStyleSheet("color: #95A5A6;"
                                 "font-size:15px;"
                                 ""
                                 "");
    playerNameLbl= new QLabel("Name");
    playerNameLbl->setStyleSheet("color: #95A5A6;"
                                 "font-size:15px;"
                                 ""
                                 "");
    posLbl = new QLabel("Position");
    posLbl->setStyleSheet("color: #95A5A6;"
                                 "font-size:15px;"
                                 ""
                                 "");
    birthdayLbl  = new QLabel("Birthday");
    birthdayLbl->setStyleSheet("color: #95A5A6;"
                                 "font-size:15px;"
                                 ""
                                 "");
    heightLbl = new QLabel("Height (m)");
    heightLbl->setStyleSheet("color: #95A5A6;"
                                 "font-size:15px;"
                                 ""
                                 "");
    weightLbl  = new QLabel("Weight (kg)");
    weightLbl->setStyleSheet("color: #95A5A6;"
                                 "font-size:15px;"
                                 ""
                                 "");
    countryLbl= new QLabel("Nationality");
    countryLbl->setStyleSheet("color: #95A5A6;"
                                 "font-size:15px;"
                                 ""
                                 "");
    teamTypeLbl = new QLabel("Team type");
    teamTypeLbl->setStyleSheet("color: #95A5A6;"
                                 "font-size:15px;"
                                 ""
                                 "");
    inClubSinceLbl = new QLabel("Signed at PSG");
    inClubSinceLbl->setStyleSheet("color: #95A5A6;"
                                 "font-size:15px;"
                                 ""
                                 "");
    contractEndsAtLbl = new QLabel("Contract ends at");
    contractEndsAtLbl->setStyleSheet("color: #95A5A6;"
                                 "font-size:15px;"
                                 ""
                                 "");
    salaryLbl = new QLabel("Salary per year ($)");
    salaryLbl->setStyleSheet("color: #95A5A6;"
                                 "font-size:15px;"
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
            sinceInClub = new Label(dateTimeConverter.toString("yyyy-MM-dd").replace(" ", ""));
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

        name = new Label("Player name");

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
    globalLay->addLayout(clubInfoLay);
    globalLay->addLayout(personInfoLay);
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


void PlayerNote::setPlayerPositionComboList(QSqlQuery &query)
{
    fromLabelToComboList(query, "name", position);
}

void PlayerNote::setTeamTypesComboList(QSqlQuery &query)
{
    fromLabelToComboList(query, "name", teamType);
}

void PlayerNote::setCountryComboList(QSqlQuery &query)
{
    fromLabelToComboList(query, "name", countryFrom);
}

void PlayerNote::setNoteViewType(const NOTE_VIEW_TYPE type)
{
    BaseNote::setNoteViewType(type);
    if(noteViewType == WRITE){
        createModifyView();
        insertFieldsInMap();
    }
}

void PlayerNote::setStyles()
{
    gameNumber->setStyleSheet("color:white;"
                              "font-size: 25px;");
    name->setStyleSheet("color:white;"
                              "font-size: 45px;");
    position->setStyleSheet("color:white;"
                              "font-size: 25px;");
    birthdayDate->setStyleSheet("color:white;"
                              "font-size: 25px;");
    height->setStyleSheet("color:white;"
                              "font-size: 25px;");
    weight->setStyleSheet("color:white;"
                              "font-size: 25px;");
    countryFrom->setStyleSheet("color:white;"
                              "font-size: 25px;");
    teamType->setStyleSheet("color:white;"
                              "font-size: 25px;");
    sinceInClub->setStyleSheet("color:white;"
                              "font-size: 25px;");
    contractEndsAt->setStyleSheet("color:white;"
                              "font-size: 25px;");
    salary->setStyleSheet("color:green;"
                              "font-size: 25px;");
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

    fieldsMap.insert(std::make_pair("inclubsincePREV", new Label(valuesBeforeAction.find(&sinceInClub)->second)));
    fieldsMap.insert(std::make_pair("leftfromclubPREV", new Label(valuesBeforeAction.find(&contractEndsAt)->second)));
    fieldsMap.insert(std::make_pair("yearsalaryPREV", new Label(valuesBeforeAction.find(&salary)->second)));
}

void PlayerNote::saveDataBeforeAction()
{
    valuesBeforeAction.clear();
    valuesBeforeAction.insert(std::make_pair(&gameNumber, gameNumber->getText()));
    valuesBeforeAction.insert(std::make_pair(&name, name->getText()));
    valuesBeforeAction.insert(std::make_pair(&position, position->getText()));
    valuesBeforeAction.insert(std::make_pair(&birthdayDate, birthdayDate->getText()));
    valuesBeforeAction.insert(std::make_pair(&weight, weight->getText()));
    valuesBeforeAction.insert(std::make_pair(&height, height->getText()));
    valuesBeforeAction.insert(std::make_pair(&countryFrom, countryFrom->getText()));
    valuesBeforeAction.insert(std::make_pair(&teamType, teamType->getText()));
    valuesBeforeAction.insert(std::make_pair(&sinceInClub, sinceInClub->getText()));
    valuesBeforeAction.insert(std::make_pair(&contractEndsAt, contractEndsAt->getText()));
    valuesBeforeAction.insert(std::make_pair(&salary, salary->getText()));
}


void PlayerNote::transformNoteInLabelView()
{
    fromDataWidgetToLabel(gameNumber, gameNumber->getText());
    fromDataWidgetToLabel(name, name->getText());
    fromDataWidgetToLabel(position, position->getText());
    fromDataWidgetToLabel(birthdayDate, birthdayDate->getText());
    fromDataWidgetToLabel(height, height->getText());
    fromDataWidgetToLabel(weight, weight->getText());
    fromDataWidgetToLabel(countryFrom, countryFrom->getText());
    fromDataWidgetToLabel(teamType, teamType->getText());
    fromDataWidgetToLabel(sinceInClub, sinceInClub->getText());
    fromDataWidgetToLabel(contractEndsAt, contractEndsAt->getText());
    fromDataWidgetToLabel(salary, salary->getText());

    setAllDataOnLayout();
}

bool PlayerNote::isInsertingDataCorrect() const
{
    QDateTime dateTimeCheck = QDateTime::fromString(birthdayDate->getText().replace(" ", ""), "yyyy-MM-dd");
    if(!dateTimeCheck.isValid()){
        QMessageBox::warning(nullptr, "Bad inserted value", "Your date is incorrect. Example: 2022-16-12");
        return false;
    }

    dateTimeCheck = QDateTime::fromString(sinceInClub->getText().replace(" ", ""), "yyyy-MM-dd");
    if(!dateTimeCheck.isValid()){
        QMessageBox::warning(nullptr, "Bad inserted value", "Your date is incorrect. Example: 2022-16-12");
        return false;
    }

    dateTimeCheck = QDateTime::fromString(contractEndsAt->getText().replace(" ", ""), "yyyy-MM-dd");
    if(!dateTimeCheck.isValid()){
        QMessageBox::warning(nullptr, "Bad inserted value", "Your date is incorrect. Example: 2022-16-12");
        return false;
    }
    if(name->getText().size() == 0){
        QMessageBox::warning(nullptr, "Bad inserted value", "Player`s name is empty");
        return false;
    }

    if(salary->getText().size() == 0){
        QMessageBox::warning(nullptr, "Bad inserted value", "Salary value is empty. Example: 1234,56");
        return false;
    }
    if(gameNumber->getText().size() == 0){
        QMessageBox::warning(nullptr, "Bad inserted value", "Game number is empty.");
        return false;
    }
    if(height->getText().size() == 0){
        QMessageBox::warning(nullptr, "Bad inserted value", "Height value is empty. Example: 1.85");
        return false;
    }
    if(weight->getText().size() == 0){
        QMessageBox::warning(nullptr, "Bad inserted value", "Weight value is empty.");
        return false;
    }
    return true;
}

QString PlayerNote::deleteNotNeedSymbolsInSalaryValue(QString salaryValue) const
{
    salaryValue = salaryValue.simplified();
    salaryValue.replace(" ", "");
    return salaryValue.replace("?", "");
}

void PlayerNote::createModifyView()
{
    saveDataBeforeAction();
    QRegularExpression regularExprGameNumber("[1-9]\\d");
    QValidator *validatorGameNumber = new QRegularExpressionValidator(regularExprGameNumber);
    fromLabelToLineEdit(gameNumber, validatorGameNumber);

    QRegularExpression regularExprName("[A-Za-z0-9\\s]{1,60}");
    QValidator *validatorName = new QRegularExpressionValidator(regularExprName);
    fromLabelToLineEdit(name, validatorName);

    notifyObservers(GET_PLAYER_POSES, this);
    fromLabelToDateTimeText(birthdayDate);

    QRegularExpression regularExprHeight("[0-2]{1}.\\d{1,2}");
    QValidator *validatorHeight = new QRegularExpressionValidator(regularExprHeight);
    fromLabelToLineEdit(height, validatorHeight);

    QRegularExpression regularExprWeight("[1-9]\\d{1,2}");
    QValidator *validatorWeight = new QRegularExpressionValidator(regularExprWeight);
    fromLabelToLineEdit(weight, validatorWeight);

    notifyObservers(GET_COUNTRIES, this);
    fromLabelToDateTimeText(sinceInClub);
    fromLabelToDateTimeText(contractEndsAt);
    notifyObservers(GET_TEAM_TYPES, this);

    QRegularExpression regularExprSalary("\\d*,\\d\\d");
    QValidator *validatorSalary = new QRegularExpressionValidator(regularExprSalary);
    fromLabelToLineEdit(salary, validatorSalary);

    setAllDataOnLayout();
    setSaveCancelButtonsVisability(true);
    setDeleteButtonVisability(false);
    modifyButton->setVisible(false);
}

void PlayerNote::modifyNoteView()
{
    createModifyView();
}

void PlayerNote::onSaveChangesClicked()
{
    if(isInsertingDataCorrect()){
        insertFieldsInMap();
        notifyObservers(UPDATE, this);
        if(isLastRequestSuccess){
            setSaveCancelButtonsVisability(false);
            setDeleteButtonVisability(true);
            modifyButton->setVisible(true);
            transformNoteInLabelView();
            setStyles();
        }
    }
}

void PlayerNote::onCancelModifyingClicked()
{
    if(lastRequestType == POST){ //Added and pressed "cancel"
        notifyObservers(DELETE, this);
        return;
    }
    setSaveCancelButtonsVisability(false);
    setDeleteButtonVisability(true);
    modifyButton->setVisible(true);
    setSavedDataBack();
    transformNoteInLabelView();
    setStyles();
}

void PlayerNote::onDeleteButtonClicked()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Delete note");
    msgBox.setText("Are you sure that you want to delete this note?");
    msgBox.setStyleSheet("background-color:#3d4c78;"
                         "color: white;"
                         "font-size: 20px;"
                         "");
    msgBox.setStandardButtons(QMessageBox::Yes);
    msgBox.addButton(QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    if(msgBox.exec() == QMessageBox::Yes){
      notifyObservers(DELETE, this);
    }else {

    }
}


