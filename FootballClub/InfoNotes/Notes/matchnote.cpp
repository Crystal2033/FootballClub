/***************************************************************************
 *                                                                         *
 *   Copyright (C) 12.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "matchnote.h"

#include "InfoNotes/DataWidgets/label.h"

MatchNote::MatchNote(QSqlQuery& query, QSqlRecord & record, QWidget* parent)
    :BaseNote(parent)
{
    recordId = query.value(record.indexOf("gameid")).toInt();
    team1 = new Label(query.value(record.indexOf("team1")).toString());
    teamType1 = new Label(query.value(record.indexOf("teamtype1")).toString());
    team2 = new Label(query.value(record.indexOf("team2")).toString());
    teamType2 = new Label(query.value(record.indexOf("teamtype2")).toString());
    finalScore = new Label(query.value(record.indexOf("finalscore")).toString());
    stadium = new Label(query.value(record.indexOf("stadium")).toString());
    gameDate = new Label(query.value(record.indexOf("gamedate")).toString());
    tournament = new Label(query.value(record.indexOf("tourname")).toString());
    stage = new Label(query.value(record.indexOf("stage")).toString());

    globalLay = new QHBoxLayout;
    leftWidgetsLay = new QVBoxLayout;
    middleWidgetsLay = new QVBoxLayout;
    rightWidgetsLay = new QVBoxLayout;

    globalLay->addLayout(leftWidgetsLay);
    globalLay->addLayout(middleWidgetsLay);
    globalLay->addLayout(rightWidgetsLay);
    setLayout(globalLay);

    leftWidgetsLay->addWidget(team1);
    leftWidgetsLay->addWidget(teamType1);

    middleWidgetsLay->addWidget(tournament);
    middleWidgetsLay->addWidget(stage);
    middleWidgetsLay->addWidget(finalScore);
    middleWidgetsLay->addWidget(gameDate);
    middleWidgetsLay->addWidget(stadium);

    rightWidgetsLay->addWidget(team2);
    rightWidgetsLay->addWidget(teamType2);

    rightWidgetsLay->addWidget(modifyButton, 0, Qt::AlignBottom);
}

void MatchNote::extend()
{
    //for future
}

void MatchNote::modifyNoteView()
{
    //TODO:
}
