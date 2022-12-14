/***************************************************************************
 *                                                                         *
 *   Copyright (C) 12.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "matchnote.h"

MatchNote::MatchNote(QSqlQuery& query, QSqlRecord & record)
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

}

void MatchNote::extend()
{
    //for future
}

void MatchNote::modifyNoteView()
{

}
