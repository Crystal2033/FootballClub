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
        name = new Label("");
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

}

void ManagerNote::setNoteViewType(const NOTE_VIEW_TYPE type)
{

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
    titleLay->addWidget(titleLbl, 0, Qt::AlignCenter);
    titleLay->addWidget(title, 0, Qt::AlignCenter);

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

void ManagerNote::setAllDataOnLayout()
{

}

void ManagerNote::insertFieldsInMap()
{

}

void ManagerNote::transformNoteInLabelView()
{

}

void ManagerNote::setTeamTypesComboList(QSqlQuery &query)
{

}

void ManagerNote::setManagerTitleComboList(QSqlQuery &query)
{

}

void ManagerNote::setCountryComboList(QSqlQuery &query)
{

}

void ManagerNote::modifyNoteView()
{

}

void ManagerNote::onSaveChangesClicked()
{

}

void ManagerNote::onCancelModifyingClicked()
{

}

void ManagerNote::onDeleteButtonClicked()
{

}
