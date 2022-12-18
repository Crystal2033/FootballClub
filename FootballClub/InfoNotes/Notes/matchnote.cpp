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
    tournInfoLbl = new QLabel("Tournament");
    tournInfoLbl->setStyleSheet("color: #3A40B0;"
                                               "font-size:10px;"
                                               ""
                                               "");
    stageInfoLbl = new QLabel("Stage");
    stageInfoLbl->setStyleSheet("color: #3A40B0;"
                                               "font-size:10px;"
                                               ""
                                               "");
    teamTypeLbl = new QLabel("Team type");
    teamTypeLbl->setStyleSheet("color: #3A40B0;"
                                               "font-size:10px;"
                                               ""
                                               "");
    firstClubLbl = new QLabel("Team");
    firstClubLbl->setStyleSheet("color: #3A40B0;"
                                               "font-size:10px;"
                                               ""
                                               "");
    finalScoreLbl = new QLabel("Score");
    finalScoreLbl->setStyleSheet("color: #3A40B0;"
                                               "font-size:10px;"
                                               ""
                                               "");
    secondClubLbl = new QLabel("Team");
    secondClubLbl->setStyleSheet("color: #3A40B0;"
                                               "font-size:10px;"
                                               ""
                                               "");
    stadiumLbl = new QLabel("Stadium");
    stadiumLbl->setStyleSheet("color: #3A40B0;"
                                               "font-size:10px;"
                                               ""
                                               "");
    dateLbl = new QLabel("Date");
    dateLbl->setStyleSheet("color: #3A40B0;"
                                               "font-size:10px;"
                                               ""
                                               "");

    if(query != nullptr){
        QSqlRecord record = query->record();
        recordId = query->value(record.indexOf("gameid")).toInt();
        club1 = new Label(query->value(record.indexOf("club1")).toString());

        teamType1 = new Label(query->value(record.indexOf("teamtype1")).toString()); //Taking one because second teams have to has the same type
        club2 = new Label(query->value(record.indexOf("club2")).toString());

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
        club1 = new Label("");

        teamType1 = new Label(""); //Taking one because second teams have to has the same type
        club2 = new Label("");
        //teamType2 = new Label(query->value(record.indexOf("teamtype2")).toString());
        finalScore = new Label("0:0");
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
    tournLayInfo = new QVBoxLayout;

    stageLay = new QHBoxLayout;
    stageLayInfo = new QVBoxLayout;

    teamsTypeLay = new QHBoxLayout;
    teamsTypeLayInfo = new QVBoxLayout;

    clubsAndScoreLay = new QHBoxLayout;
    firstClubLay = new QVBoxLayout;
    finaScoreLay = new QVBoxLayout;
    secondClubLay = new QVBoxLayout;

    stadiumLay = new QHBoxLayout;
    stadiumLayInfo = new QVBoxLayout;

    dateLay = new QHBoxLayout;
    dateLayInfo = new QVBoxLayout;

    modifyButtonsLay = new QHBoxLayout;
    deleteNoteButtonLay = new QHBoxLayout;

    tournLay->addLayout(tournLayInfo);
    stageLay->addLayout(stageLayInfo);
    teamsTypeLay->addLayout(teamsTypeLayInfo);
    clubsAndScoreLay->addLayout(firstClubLay);
    clubsAndScoreLay->addLayout(finaScoreLay);
    clubsAndScoreLay->addLayout(secondClubLay);
    stadiumLay->addLayout(stadiumLayInfo);
    dateLay->addLayout(dateLayInfo);

    setAllDataOnLayout();

    deleteNoteButtonLay->addWidget(deleteNoteButton, 0, Qt::AlignRight);
    modifyButtonsLay->addWidget(cancelSaving, 0, Qt::AlignCenter);
    cancelSaving->setVisible(false);
    modifyButtonsLay->addWidget(saveChangesButton, 0, Qt::AlignCenter);
    saveChangesButton->setVisible(false);
    modifyButtonsLay->addWidget(modifyButton, 0, Qt::AlignRight);


    globalLay->addLayout(deleteNoteButtonLay);
    globalLay->addLayout(tournLay);
    globalLay->addLayout(stageLay);
    globalLay->addLayout(teamsTypeLay);
    globalLay->addLayout(clubsAndScoreLay);
    globalLay->addLayout(stadiumLay);
    globalLay->addLayout(dateLay);
    globalLay->addLayout(modifyButtonsLay);

    setLayout(globalLay);

    connect(modifyButton, &QPushButton::clicked, this, &MatchNote::modifyNoteView);
    connect(saveChangesButton, &QPushButton::clicked, this, &MatchNote::onSaveChangesClicked);
    connect(cancelSaving, &QPushButton::clicked, this, &MatchNote::onCancelModifyingClicked);
    connect(deleteNoteButton, &QPushButton::clicked, this, &MatchNote::onDeleteButtonClicked);

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

void MatchNote::setClubsComboList(QSqlQuery &query)
{
    fromLabelToComboList(query, "name", club1);

    QRegularExpression regularExpr("[\\d]*:[\\d]*");
    QValidator *validator = new QRegularExpressionValidator(regularExpr);
    fromLabelToLineEdit(finalScore, validator);

    Label* lbl = (Label*) club2;
    QString lastValue = lbl->getText();
    ComboBox* firstClubBox = (ComboBox*)club1;
    std::map<QString, unsigned> valueAndIdMap = firstClubBox->getValueAndIdMap();
    delete club2;

    club2 = new ComboBox(valueAndIdMap);
    ComboBox* temp = (ComboBox*) club2;

    temp->setCurrentItem(lastValue);
}

void MatchNote::setStadiumsComboList(QSqlQuery &query)
{
    fromLabelToComboList(query, "name", stadium);
}

void MatchNote::setNoteViewType(const NOTE_VIEW_TYPE type)
{
    BaseNote::setNoteViewType(type);
    if(noteViewType == WRITE){
        createModifyView();
        insertFieldsInMap();
    }
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
    createModifyView();
}

void MatchNote::onSaveChangesClicked()
{
    if(isInsertingDataCorrect()){
        insertFieldsInMap();
        notifyObservers(UPDATE, this);
        setSaveCancelButtonsVisability(false);
        modifyButton->setVisible(true);
        transformNoteInLabelView();
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

void MatchNote::onDeleteButtonClicked()
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
    fieldsMap.insert(std::make_pair("stadium", stadium));
    fieldsMap.insert(std::make_pair("club1", club1));
    fieldsMap.insert(std::make_pair("club2", club2));
    fieldsMap.insert(std::make_pair("teamtype", teamType1));
    fieldsMap.insert(std::make_pair("finalscore", finalScore));
    fieldsMap.insert(std::make_pair("stage", stage));
    fieldsMap.insert(std::make_pair("gameDate", gameDate));
    fieldsMap.insert(std::make_pair("tournament", tournament));
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
    valuesBeforeAction.insert(std::make_pair(&club1, club1->getText()));
    valuesBeforeAction.insert(std::make_pair(&teamType1, teamType1->getText()));
    valuesBeforeAction.insert(std::make_pair(&club2, club2->getText()));
    valuesBeforeAction.insert(std::make_pair(&finalScore, finalScore->getText()));
    valuesBeforeAction.insert(std::make_pair(&stadium, stadium->getText()));
    valuesBeforeAction.insert(std::make_pair(&gameDate, gameDate->getText()));
    valuesBeforeAction.insert(std::make_pair(&tournament, tournament->getText()));
    valuesBeforeAction.insert(std::make_pair(&stage, stage->getText()));
}

void MatchNote::transformNoteInLabelView()
{
    fromDataWidgetToLabel(club1, club1->getText());
    fromDataWidgetToLabel(teamType1, teamType1->getText());
    fromDataWidgetToLabel(club2, club2->getText());
    fromDataWidgetToLabel(finalScore, finalScore->getText());
    fromDataWidgetToLabel(stadium, stadium->getText());
    fromDataWidgetToLabel(gameDate, gameDate->getText());
    fromDataWidgetToLabel(tournament, tournament->getText());
    fromDataWidgetToLabel(stage, stage->getText());

    setAllDataOnLayout();
}

void MatchNote::setAllDataOnLayout()
{

    tournLayInfo->addWidget(tournInfoLbl, 0, Qt::AlignCenter);
    tournLayInfo->addWidget(tournament, 0, Qt::AlignCenter);




    stageLayInfo->addWidget(stageInfoLbl, 0, Qt::AlignCenter);
    stageLayInfo->addWidget(stage, 0, Qt::AlignCenter);




    teamsTypeLayInfo->addWidget(teamTypeLbl, 0, Qt::AlignCenter);
    teamsTypeLayInfo->addWidget(teamType1, 0, Qt::AlignCenter);



    firstClubLay->addWidget(firstClubLbl, 0, Qt::AlignCenter);
    firstClubLay->addWidget(club1, 0, Qt::AlignCenter);



    finaScoreLay->addWidget(finalScoreLbl, 0, Qt::AlignCenter);
    finaScoreLay->addWidget(finalScore, 0, Qt::AlignCenter);



    secondClubLay->addWidget(secondClubLbl, 0, Qt::AlignCenter);
    secondClubLay->addWidget(club2, 0, Qt::AlignCenter);



    stadiumLayInfo->addWidget(stadiumLbl, 0, Qt::AlignCenter);
    stadiumLayInfo->addWidget(stadium, 0, Qt::AlignCenter);



    dateLayInfo->addWidget(dateLbl, 0, Qt::AlignCenter);
    dateLayInfo->addWidget(gameDate, 0, Qt::AlignCenter);

}

void MatchNote::createModifyView()
{
    saveDataBeforeAction();
    notifyObservers(GET_TOURNS, this); //getting list of names for combobox
    notifyObservers(GET_STAGES, this);
    notifyObservers(GET_TEAM_TYPES, this);
    notifyObservers(GET_CLUBS, this);
    fromLabelToDateTimeText(gameDate);
    notifyObservers(GET_STADIUMS, this);
    setAllDataOnLayout();
    setSaveCancelButtonsVisability(true);
    modifyButton->setVisible(false);
}
