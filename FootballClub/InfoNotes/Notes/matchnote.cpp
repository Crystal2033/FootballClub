/***************************************************************************
 *                                                                         *
 *   Copyright (C) 12.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "matchnote.h"
#include "InfoNotes/DataWidgets/combobox.h"
#include "InfoNotes/DataWidgets/label.h"

#include <QDateTime>

MatchNote::MatchNote(QSqlQuery* query, QWidget* parent)
    :BaseNote(parent)
{
    if(query != nullptr){
        QSqlRecord record = query->record();
        recordId = query->value(record.indexOf("gameid")).toInt();
        team1 = new Label(query->value(record.indexOf("team1")).toString());

        teamType1 = new Label(query->value(record.indexOf("teamtype1")).toString()); //Taking one because second teams have to has the same type
        team2 = new Label(query->value(record.indexOf("team2")).toString());
        //teamType2 = new Label(query->value(record.indexOf("teamtype2")).toString());
        finalScore = new Label(query->value(record.indexOf("finalscore")).toString());
        stadium = new Label(query->value(record.indexOf("stadium")).toString());
        QDateTime dateTimeConverter = QDateTime::fromString(query->value(record.indexOf("gamedate")).toString(), "yyyy-MM-ddTHH:mm:ss.zzz");
        if(!dateTimeConverter.isValid()){
            gameDate = new Label("Bad format date");
        }
        else{
            gameDate = new Label(dateTimeConverter.toString("yyyy-MM-dd hh:mm:ss"));
        }

        tournament = new Label(query->value(record.indexOf("tournname")).toString());
        stage = new Label(query->value(record.indexOf("stage")).toString());
    }
    else{
        recordId = 0;
        team1 = new Label("");

        teamType1 = new Label(""); //Taking one because second teams have to has the same type
        team2 = new Label("");
        //teamType2 = new Label(query->value(record.indexOf("teamtype2")).toString());
        finalScore = new Label("");
        stadium = new Label("");
        QDateTime dateTimeConverter = QDateTime::currentDateTime();
        if(!dateTimeConverter.isValid()){
            gameDate = new Label("Bad format date");
        }
        else{
            gameDate = new Label(dateTimeConverter.toString("yyyy-MM-dd hh:mm:ss"));
        }

        tournament = new Label("");
        stage = new Label("");
    }


    globalLay = new QVBoxLayout;

    tournLay = new QHBoxLayout;
    stageLay = new QHBoxLayout;
    teamsTypeLay = new QHBoxLayout;
    teamsAndScoreLay = new QHBoxLayout;
    stadiumLay = new QHBoxLayout;
    dateLay = new QHBoxLayout;
    buttonsLay = new QHBoxLayout;
    deleteNoteButtonLay = new QHBoxLayout;

    setAllDataOnLayout();

    deleteNoteButtonLay->addWidget(deleteNoteButton, 0, Qt::AlignRight);
    buttonsLay->addWidget(cancelSaving, 0, Qt::AlignCenter);
    cancelSaving->setVisible(false);
    buttonsLay->addWidget(saveChangesButton, 0, Qt::AlignCenter);
    saveChangesButton->setVisible(false);
    buttonsLay->addWidget(modifyButton, 0, Qt::AlignRight);

    globalLay->addLayout(deleteNoteButtonLay);
    globalLay->addLayout(tournLay);
    globalLay->addLayout(stageLay);
    globalLay->addLayout(teamsTypeLay);
    globalLay->addLayout(teamsAndScoreLay);
    globalLay->addLayout(stadiumLay);
    globalLay->addLayout(dateLay);
    globalLay->addLayout(buttonsLay);

    setLayout(globalLay);

    connect(modifyButton, &QPushButton::clicked, this, &MatchNote::modifyNoteView);
    connect(saveChangesButton, &QPushButton::clicked, this, &MatchNote::onSaveChangesClicked);
    connect(cancelSaving, &QPushButton::clicked, this, &MatchNote::onCancelModifyingClicked);

    setStyles();
}

void MatchNote::setTournamentComboList(QSqlQuery &query)
{
    fromLabelToComboList(query, "name", tournament);
}

void MatchNote::setStagesComboList(QSqlQuery &query)
{
    fromLabelToComboList(query, "name", stage);
}

void MatchNote::setTeamTypesComboList(QSqlQuery &query)
{
    fromLabelToComboList(query, "name", teamType1);
}

void MatchNote::setClubsComboListAndScore(QSqlQuery &query)
{

    fromLabelToComboList(query, "name", team1);

    QRegularExpression regularExpr("[\\d]*:[\\d]*");
    QValidator *validator = new QRegularExpressionValidator(regularExpr);
    fromLabelToLineEdit(finalScore, validator);

    Label* lbl = (Label*) team2;
    QString lastValue = lbl->getText();
    ComboBox* firstTeam = (ComboBox*)team1;
    std::map<QString, unsigned> valueAndIdMap = firstTeam->getValueAndIdMap();
    delete team2;

    team2 = new ComboBox(valueAndIdMap);
    ComboBox* temp = (ComboBox*) team2;

    temp->setCurrentItem(lastValue);
}

void MatchNote::setStadiumsComboList(QSqlQuery &query)
{
    fromLabelToComboList(query, "name", stadium);
}

std::map<QString, TextField *> MatchNote::getFieldsMap() const
{
    return fieldsMap;
}


MatchNote::~MatchNote()
{
    removeObservers();
    fieldsMap.clear();
}

void MatchNote::extend()
{
    //for future
}

void MatchNote::modifyNoteView()
{
    saveDataBeforeAction();
    notifyObservers(MATCH_TOURNS, this); //getting list of names for combobox
    notifyObservers(MATCH_STAGES, this);
    notifyObservers(MATCH_TEAM_TYPES, this);
    notifyObservers(MATCH_CLUBS, this);
    fromLabelToDateTimeText(gameDate);
    notifyObservers(MATCH_STADIUMS, this);
    setAllDataOnLayout();
    setSaveCancelButtonsVisability(true);
    modifyButton->setVisible(false);

}

void MatchNote::onSaveChangesClicked()
{
    if(isInsertingDataCorrect()){
        insertFieldsInMap();
        notifyObservers(MATCH_UPDATE, this);
        setSaveCancelButtonsVisability(false);
        modifyButton->setVisible(true);
        setStyles();
    }
}

void MatchNote::onCancelModifyingClicked()
{
    setSaveCancelButtonsVisability(false);
    modifyButton->setVisible(true);
    setSavedDataBack();
    transformNoteInLabelView();
    setStyles();
}

void MatchNote::setStyles()
{
    tournament->setStyleSheet("font-size: 40px;"
                              "color: white;"
                              "font-weight: bold;"
                              "font-family: Goudy Old Style;"
                              "");
}

void MatchNote::insertFieldsInMap()
{
    fieldsMap.clear();
    fieldsMap.insert(std::make_pair("team1", team1));
    fieldsMap.insert(std::make_pair("teamtype", teamType1));
    fieldsMap.insert(std::make_pair("team2", team2));
    fieldsMap.insert(std::make_pair("finalscore", finalScore));
    fieldsMap.insert(std::make_pair("stadium", stadium));
    fieldsMap.insert(std::make_pair("gameDate", gameDate));
    fieldsMap.insert(std::make_pair("tournament", tournament));
    fieldsMap.insert(std::make_pair("stage", stage));
}

bool MatchNote::isInsertingDataCorrect() const
{
    QRegularExpression regularExpr("[\\d]+:[\\d]+");
    if(!regularExpr.match(finalScore->getText()).hasMatch()){
        QMessageBox::warning(nullptr, "Bad inserted value", "Your final score value is incorrect. Example: 0:1");
        return false;
    }

    QDateTime dateTimeCheck = QDateTime::fromString(gameDate->getText(), "yyyy-MM-dd hh:mm:ss");
    if(!dateTimeCheck.isValid()){
        QMessageBox::warning(nullptr, "Bad inserted value", "Your game date or time value is incorrect. Example: 2022-16-12 18:10:12");
        return false;
    }
    return true;
}

void MatchNote::saveDataBeforeAction()
{
    valuesBeforeAction.clear();
    valuesBeforeAction.insert(std::make_pair(&team1, team1->getText()));
    valuesBeforeAction.insert(std::make_pair(&teamType1, teamType1->getText()));
    valuesBeforeAction.insert(std::make_pair(&team2, team2->getText()));
    valuesBeforeAction.insert(std::make_pair(&finalScore, finalScore->getText()));
    valuesBeforeAction.insert(std::make_pair(&stadium, stadium->getText()));
    valuesBeforeAction.insert(std::make_pair(&gameDate, gameDate->getText()));
    valuesBeforeAction.insert(std::make_pair(&tournament, tournament->getText()));
    valuesBeforeAction.insert(std::make_pair(&stage, stage->getText()));
}

void MatchNote::setSavedDataBack()
{
    if(!valuesBeforeAction.empty()){
        for(auto textField : valuesBeforeAction){
            (*textField.first)->setText(textField.second);
        }
    }
}

void MatchNote::transformNoteInLabelView()
{
    fromDataWidgetToLabel(team1, team1->getText());
    fromDataWidgetToLabel(teamType1, teamType1->getText());
    fromDataWidgetToLabel(team2, team2->getText());
    fromDataWidgetToLabel(finalScore, finalScore->getText());
    fromDataWidgetToLabel(stadium, stadium->getText());
    fromDataWidgetToLabel(gameDate, gameDate->getText());
    fromDataWidgetToLabel(tournament, tournament->getText());
    fromDataWidgetToLabel(stage, stage->getText());

    setAllDataOnLayout();
}

void MatchNote::setAllDataOnLayout()
{
    tournLay->addWidget(tournament, 0, Qt::AlignCenter);
    stageLay->addWidget(stage, 0, Qt::AlignCenter);
    teamsTypeLay->addWidget(teamType1, 0, Qt::AlignCenter);
    teamsAndScoreLay->addWidget(team1, 0, Qt::AlignCenter);
    teamsAndScoreLay->addWidget(finalScore, 0, Qt::AlignCenter);
    teamsAndScoreLay->addWidget(team2, 0, Qt::AlignCenter);
    stadiumLay->addWidget(stadium, 0, Qt::AlignCenter);
    dateLay->addWidget(gameDate, 0, Qt::AlignCenter);
}
