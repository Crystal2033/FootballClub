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

MatchNote::MatchNote(QSqlQuery& query, QWidget* parent)
    :BaseNote(parent)
{
    QSqlRecord record = query.record();
    recordId = query.value(record.indexOf("gameid")).toInt();
    team1 = new Label(query.value(record.indexOf("team1")).toString());

    teamType1 = new Label(query.value(record.indexOf("teamtype1")).toString()); //Taking one because second teams have to has the same type
    team2 = new Label(query.value(record.indexOf("team2")).toString());
    //teamType2 = new Label(query.value(record.indexOf("teamtype2")).toString());
    finalScore = new Label(query.value(record.indexOf("finalscore")).toString());
    stadium = new Label(query.value(record.indexOf("stadium")).toString());
    QDateTime dateTimeConverter = QDateTime::fromString(query.value(record.indexOf("gamedate")).toString(), "yyyy-MM-ddTHH:mm:ss.zzz");
    if(!dateTimeConverter.isValid()){
        gameDate = new Label("Bad format date");
    }
    else{
        gameDate = new Label(dateTimeConverter.toString("yyyy-MM-dd hh:mm:ss"));
    }

    tournament = new Label(query.value(record.indexOf("tournname")).toString());
    stage = new Label(query.value(record.indexOf("stage")).toString());


    globalLay = new QVBoxLayout;

    tournLay = new QHBoxLayout;
    stageLay = new QHBoxLayout;
    teamsType = new QHBoxLayout;
    teamsAndScoreLay = new QHBoxLayout;
    stadiumLay = new QHBoxLayout;
    dateLay = new QHBoxLayout;
    buttonsLay = new QHBoxLayout;

    tournLay->addWidget(tournament, 0, Qt::AlignCenter);
    stageLay->addWidget(stage, 0, Qt::AlignCenter);
    teamsType->addWidget(teamType1, 0, Qt::AlignCenter);
    teamsAndScoreLay->addWidget(team1, 0, Qt::AlignCenter);
    teamsAndScoreLay->addWidget(finalScore, 0, Qt::AlignCenter);
    teamsAndScoreLay->addWidget(team2, 0, Qt::AlignCenter);
    stadiumLay->addWidget(stadium, 0, Qt::AlignCenter);
    dateLay->addWidget(gameDate, 0, Qt::AlignCenter);

    buttonsLay->addWidget(cancelSaving, 0, Qt::AlignCenter);
    cancelSaving->setVisible(false);
    buttonsLay->addWidget(saveChangesButton, 0, Qt::AlignCenter);
    saveChangesButton->setVisible(false);
    buttonsLay->addWidget(modifyButton, 0, Qt::AlignRight);

    globalLay->addLayout(tournLay);
    globalLay->addLayout(stageLay);
    globalLay->addLayout(teamsType);
    globalLay->addLayout(teamsAndScoreLay);
    globalLay->addLayout(stadiumLay);
    globalLay->addLayout(dateLay);
    globalLay->addLayout(buttonsLay);

    setLayout(globalLay);

    connect(modifyButton, &QPushButton::clicked, this, &MatchNote::modifyNoteView);
    connect(saveChangesButton, &QPushButton::clicked, this, &MatchNote::onSaveChangesClicked);
    connect(cancelSaving, &QPushButton::clicked, this, &MatchNote::onCancelSavingClicked);

    setStyles();
}

void MatchNote::setTournamentComboList(QSqlQuery &query)
{
    QSqlRecord record = query.record();
    QStringList stringList;
    while(query.next()){
        stringList << query.value(record.indexOf("name")).toString();
    }
    qInfo() << stringList;
    delete tournament;
    tournament = new ComboBox(stringList);
    tournLay->addWidget(tournament, 0, Qt::AlignCenter);
}

MatchNote::~MatchNote()
{
    removeObservers();
}

void MatchNote::extend()
{
    //for future
}

void MatchNote::modifyNoteView()
{
    cancelSaving->setVisible(true);
    saveChangesButton->setVisible(true);

    notifyObservers(MATCH_TOURNS, this); //getting list of names for combobox
    notifyObservers(MATCH_STAGES, this);
    notifyObservers(MATCH_TEAM_TYPES, this);
    notifyObservers(MATCH_CLUBS, this);
    notifyObservers(MATCH_STADIUMS, this);

}

void MatchNote::onSaveChangesClicked()
{
    qInfo() << "Save changes";
}

void MatchNote::onCancelSavingClicked()
{
    qInfo() << "Cancel saving";
}

void MatchNote::setStyles()
{
    tournament->setStyleSheet("font-size: 40px;"
                              "color: white;"
                              "font-weight: bold;"
                              "font-family: Goudy Old Style;"
                              "");
}
