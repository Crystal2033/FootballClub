/***************************************************************************
 *                                                                         *
 *   Copyright (C) 11.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "dbrepository.h"

DBRepository::DBRepository()
{
    if(!createConnection()){
        exit(-1);
    }
}

DBRepository::~DBRepository()
{
    if(database != nullptr){
        delete database;
    }
}

QString DBRepository::getMatchReadOnlyRequest() const
{
    return  "select gameid, team1, finalscore, club.club_name as team2, stadium.name as stadium, gameDate"
            " from"
            " (select game.id as gameid, club.club_name as team1, game.final_score as finalscore, game.second_team as team2, game.starts_at as gameDate, game.stadium_id as stadiumid"
            " from club, game, team, stadium where game.first_team=team.id and team.club_id=club.id and game.stadium_id=stadium.id) as subReq,"
            " team, club, stadium "
            "where subReq.team2=team.id and team.club_id=club.id and stadiumid=stadium.id"
            " order by gameDate asc;";
}

void DBRepository::testPrint()
{
    QSqlQuery query;
    if(!query.exec(getMatchReadOnlyRequest())){
        qInfo() << "Bad request";
    }
    else{
        qInfo() << "good";
    }
}

bool DBRepository::createConnection()
{
    if(database != nullptr){
        return false;
    }
    else{
        database = new DataBase;
    }
    return database->createConnection("QPSQL", "FootballClub", "postgres", "gomer2002");
}
