#include "managernote.h"
#include "InfoNotes/DataWidgets/label.h"


ManagerNote::ManagerNote(QSqlQuery* query, QWidget* parent)
    :BaseNote(parent)
{
    titleLbl = new QLabel("Title");
    titleLbl->setStyleSheet("color: #3A40B0;"
                                 "font-size:10px;"
                                 ""
                                 "");
    nameLbl = new QLabel("Name");
    nameLbl->setStyleSheet("color: #3A40B0;"
                                 "font-size:10px;"
                                 ""
                                 "");
    teamTypeLbl = new QLabel("Team type");
    teamTypeLbl->setStyleSheet("color: #3A40B0;"
                                 "font-size:10px;"
                                 ""
                                 "");
    countryLbl = new QLabel("Nationality");
    countryLbl->setStyleSheet("color: #3A40B0;"
                                 "font-size:10px;"
                                 ""
                                 "");
    birthdayLbl = new QLabel("Birthday");
    birthdayLbl->setStyleSheet("color: #3A40B0;"
                                 "font-size:10px;"
                                 ""
                                 "");
    inClubSinceLbl = new QLabel("Signed at PSG");
    inClubSinceLbl->setStyleSheet("color: #3A40B0;"
                                 "font-size:10px;"
                                 ""
                                 "");
    contractEndslbl = new QLabel("Contract ends at");
    contractEndslbl->setStyleSheet("color: #3A40B0;"
                                 "font-size:10px;"
                                 ""
                                 "");
    salarylbl = new QLabel("Salary per year ($)");
    salarylbl->setStyleSheet("color: #3A40B0;"
                                 "font-size:10px;"
                                 ""
                                 "");

    if(query != nullptr){
        QSqlRecord record = query->record();
        recordId = query->value(record.indexOf("id")).toInt();
        name = new Label(query->value(record.indexOf("name")).toString());

        title = new Label(query->value(record.indexOf("title")).toString()); //Taking one because second teams have to has the same type
        teamType = new Label(query->value(record.indexOf("teamtype")).toString());

        country = new Label(query->value(record.indexOf("borncountry")).toString());

        QDateTime dateTimeConverter = QDateTime::fromString(query->value(record.indexOf("birthday")).toString(), "yyyy-MM-dd");
        if(!dateTimeConverter.isValid()){
            birthdayDate = new Label("Bad format date");
        }
        else{
            birthdayDate = new Label(dateTimeConverter.toString("yyyy-MM-dd"));
        }

        salary = new Label(deleteNotNeedSymbolsInSalaryValue(query->value(record.indexOf("yearsalary")).toString()));

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
        name = new Label("Manager name");
        title = new Label(""); //Taking one because second teams have to has the same type
        teamType = new Label("");

        country = new Label("");

        QDateTime dateTimeConverter = QDateTime::currentDateTime();
        birthdayDate = new Label(dateTimeConverter.toString("yyyy-MM-dd"));

        salary = new Label("0");

        sinceInClub = new Label(dateTimeConverter.toString("yyyy-MM-dd"));
        contractEndsAt = new Label(dateTimeConverter.toString("yyyy-MM-dd"));
    }

    globalLay = new QVBoxLayout;

    titleLay = new QHBoxLayout;
    titleInfoLay = new QVBoxLayout;

    teamTypeInfoLay = new QHBoxLayout;
    teamTypeLay = new QVBoxLayout;

    personInfoLay = new QHBoxLayout;
    personNameLay = new QVBoxLayout;
    personCountryLay = new QVBoxLayout;
    personBirthdayLay = new QVBoxLayout;

    clubInfoLay = new QHBoxLayout;
    clubInfoSinceLay = new QVBoxLayout;
    clubInfoLeftAtLay = new QVBoxLayout;
    clubInfoSalary = new QVBoxLayout;

    modifyButtonsLay = new QHBoxLayout;
    deleteNoteButtonLay = new QHBoxLayout;


    titleInfoLay->addLayout(titleLay);

    teamTypeInfoLay->addLayout(teamTypeLay);

    personInfoLay->addLayout(personNameLay);
    personInfoLay->addLayout(personCountryLay);
    personInfoLay->addLayout(personBirthdayLay);

    clubInfoLay->addLayout(clubInfoSinceLay);
    clubInfoLay->addLayout(clubInfoLeftAtLay);
    clubInfoLay->addLayout(clubInfoSalary);


    setAllDataOnLayout();

    deleteNoteButtonLay->addWidget(deleteNoteButton, 0, Qt::AlignRight);
    modifyButtonsLay->addWidget(cancelSaving, 0, Qt::AlignCenter);
    cancelSaving->setVisible(false);
    modifyButtonsLay->addWidget(saveChangesButton, 0, Qt::AlignCenter);
    saveChangesButton->setVisible(false);
    modifyButtonsLay->addWidget(modifyButton, 0, Qt::AlignRight);

    globalLay->addLayout(deleteNoteButtonLay);
    globalLay->addLayout(titleInfoLay);
    globalLay->addLayout(teamTypeInfoLay);
    globalLay->addLayout(personInfoLay);
    globalLay->addLayout(clubInfoLay);
    globalLay->addLayout(modifyButtonsLay);

    setLayout(globalLay);

    connect(modifyButton, &QPushButton::clicked, this, &ManagerNote::modifyNoteView);
    connect(saveChangesButton, &QPushButton::clicked, this, &ManagerNote::onSaveChangesClicked);
    connect(cancelSaving, &QPushButton::clicked, this, &ManagerNote::onCancelModifyingClicked);
    connect(deleteNoteButton, &QPushButton::clicked, this, &ManagerNote::onDeleteButtonClicked);

    setStyles();

}

void ManagerNote::setNoteViewType(const NOTE_VIEW_TYPE type)
{
    BaseNote::setNoteViewType(type);
    if(noteViewType == WRITE){
        createModifyView();
        insertFieldsInMap();
    }
}

void ManagerNote::extend()
{

}

void ManagerNote::setStyles()
{

}

QString ManagerNote::deleteNotNeedSymbolsInSalaryValue(QString salaryValue) const
{
    salaryValue = salaryValue.simplified();
    salaryValue.replace(" ", "");
    return salaryValue.replace("?", "");
}

void ManagerNote::saveDataBeforeAction()
{
    valuesBeforeAction.clear();
    valuesBeforeAction.insert(std::make_pair(&title, title->getText()));
    valuesBeforeAction.insert(std::make_pair(&teamType, teamType->getText()));
    valuesBeforeAction.insert(std::make_pair(&name, name->getText()));
    valuesBeforeAction.insert(std::make_pair(&country, country->getText()));
    valuesBeforeAction.insert(std::make_pair(&birthdayDate, birthdayDate->getText()));
    valuesBeforeAction.insert(std::make_pair(&sinceInClub, sinceInClub->getText()));
    valuesBeforeAction.insert(std::make_pair(&contractEndsAt, contractEndsAt->getText()));
    valuesBeforeAction.insert(std::make_pair(&salary, salary->getText()));
}

void ManagerNote::setAllDataOnLayout()
{
    titleInfoLay->addWidget(titleLbl, 0, Qt::AlignCenter);
    titleInfoLay->addWidget(title, 0, Qt::AlignCenter);

    teamTypeLay->addWidget(teamTypeLbl, 0, Qt::AlignCenter);
    teamTypeLay->addWidget(teamType, 0, Qt::AlignCenter);

    personNameLay->addWidget(nameLbl, 0, Qt::AlignCenter);
    personNameLay->addWidget(name, 0, Qt::AlignCenter);
    personCountryLay->addWidget(countryLbl, 0, Qt::AlignCenter);
    personCountryLay->addWidget(country, 0, Qt::AlignCenter);
    personBirthdayLay->addWidget(birthdayLbl, 0, Qt::AlignCenter);
    personBirthdayLay->addWidget(birthdayDate, 0, Qt::AlignCenter);

    clubInfoSinceLay->addWidget(inClubSinceLbl, 0, Qt::AlignCenter);
    clubInfoSinceLay->addWidget(sinceInClub, 0, Qt::AlignCenter);
    clubInfoLeftAtLay->addWidget(contractEndslbl, 0, Qt::AlignCenter);
    clubInfoLeftAtLay->addWidget(contractEndsAt, 0, Qt::AlignCenter);
    clubInfoSalary->addWidget(salarylbl, 0, Qt::AlignCenter);
    clubInfoSalary->addWidget(salary, 0, Qt::AlignCenter);
}

void ManagerNote::insertFieldsInMap()
{
    fieldsMap.clear();
    fieldsMap.insert(std::make_pair("title", title));
    fieldsMap.insert(std::make_pair("teamtype", teamType));
    fieldsMap.insert(std::make_pair("name", name));
    fieldsMap.insert(std::make_pair("birthday", birthdayDate));
    fieldsMap.insert(std::make_pair("country", country));

    fieldsMap.insert(std::make_pair("inclubsince", sinceInClub));
    fieldsMap.insert(std::make_pair("leftfromclub", contractEndsAt));
    fieldsMap.insert(std::make_pair("yearsalary", salary));

    fieldsMap.insert(std::make_pair("inclubsincePREV", new Label(valuesBeforeAction.find(&sinceInClub)->second)));
    fieldsMap.insert(std::make_pair("leftfromclubPREV", new Label(valuesBeforeAction.find(&contractEndsAt)->second)));
    fieldsMap.insert(std::make_pair("yearsalaryPREV", new Label(valuesBeforeAction.find(&salary)->second)));
}

void ManagerNote::transformNoteInLabelView()
{
    fromDataWidgetToLabel(title, title->getText());
    fromDataWidgetToLabel(name, name->getText());
    fromDataWidgetToLabel(teamType, teamType->getText());
    fromDataWidgetToLabel(country, country->getText());
    fromDataWidgetToLabel(birthdayDate, birthdayDate->getText());
    fromDataWidgetToLabel(sinceInClub, sinceInClub->getText());
    fromDataWidgetToLabel(contractEndsAt, contractEndsAt->getText());
    fromDataWidgetToLabel(salary, salary->getText());

    setAllDataOnLayout();
}

void ManagerNote::setTeamTypesComboList(QSqlQuery &query)
{
    fromLabelToComboList(query, "name", teamType);
}

void ManagerNote::setManagerTitleComboList(QSqlQuery &query)
{
    fromLabelToComboList(query, "title", title);
}

void ManagerNote::setCountryComboList(QSqlQuery &query)
{
    fromLabelToComboList(query, "name", country);
}

void ManagerNote::createModifyView()
{
    saveDataBeforeAction();
    notifyObservers(GET_MANAGER_TITLES, this);
    notifyObservers(GET_TEAM_TYPES, this);

    QRegularExpression regularExprName("[A-Za-z0-9\\s]{1,60}");
    QValidator *validatorName = new QRegularExpressionValidator(regularExprName);
    fromLabelToLineEdit(name, validatorName);

    notifyObservers(GET_COUNTRIES, this);
    fromLabelToDateTimeText(birthdayDate);

    fromLabelToDateTimeText(sinceInClub);
    fromLabelToDateTimeText(contractEndsAt);

    QRegularExpression regularExprSalary("[1-9]\\d*,\\d\\d");
    QValidator *validatorSalary = new QRegularExpressionValidator(regularExprSalary);
    fromLabelToLineEdit(salary, validatorSalary);

    setAllDataOnLayout();
    setSaveCancelButtonsVisability(true);
    modifyButton->setVisible(false);
}

bool ManagerNote::isInsertingDataCorrect() const
{
    QDateTime dateTimeCheck = QDateTime::fromString(birthdayDate->getText(), "yyyy-MM-dd");
    if(!dateTimeCheck.isValid()){
        QMessageBox::warning(nullptr, "Bad inserted value", "Manager`s birthday is wrong. Example: 2022-16-12");
        return false;
    }

    dateTimeCheck = QDateTime::fromString(sinceInClub->getText(), "yyyy-MM-dd");
    if(!dateTimeCheck.isValid()){
        QMessageBox::warning(nullptr, "Bad inserted value", "Since in club date is wrong. Example: 2022-16-12");
        return false;
    }

    dateTimeCheck = QDateTime::fromString(contractEndsAt->getText(), "yyyy-MM-dd");
    if(!dateTimeCheck.isValid()){
        QMessageBox::warning(nullptr, "Bad inserted value", "Contract ends data is wrong. Example: 2022-16-12");
        return false;
    }

    if(name->getText().size() == 0){
        QMessageBox::warning(nullptr, "Bad inserted value", "Manager`s name is empty");
        return false;
    }

    if(salary->getText().size() == 0){
        QMessageBox::warning(nullptr, "Bad inserted value", "Salary value is empty. Example: 1234,56");
        return false;
    }
    return true;
}

void ManagerNote::modifyNoteView()
{
    createModifyView();
}

void ManagerNote::onSaveChangesClicked()
{
    if(isInsertingDataCorrect()){
        insertFieldsInMap();
        notifyObservers(UPDATE, this);
        if(isLastRequestSuccess){
            setSaveCancelButtonsVisability(false);
            modifyButton->setVisible(true);
            transformNoteInLabelView();
            setStyles();
        }
    }
}

void ManagerNote::onCancelModifyingClicked()
{
    if(lastRequestType == POST){ //Added and pressed "cancel"
        notifyObservers(DELETE, this);
        return;
    }
    setSaveCancelButtonsVisability(false);
    modifyButton->setVisible(true);
    setSavedDataBack();
    transformNoteInLabelView();
    setStyles();
}

void ManagerNote::onDeleteButtonClicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Delete note", "Are you sure that you want to delete this note?",
                                QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        notifyObservers(DELETE, this);
    }
    else{

    }
}
