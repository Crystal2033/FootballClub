/***************************************************************************
 *                                                                         *
 *   Copyright (C) 12.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "matchnote.h"
#include "InfoNotes/DataWidgets/label.h"

#include <QDateTime>

MatchNote::MatchNote(QSqlQuery& query, QSqlRecord & record, QWidget* parent)
    :BaseNote(parent)
{

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
    setStyles();
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

}

void MatchNote::setStyles()
{
    tournament->setStyleSheet("font-size: 40px;"
                              "color: white;"
                              "font-weight: bold;"
                              "font-family: Goudy Old Style;"
                              "");
}
