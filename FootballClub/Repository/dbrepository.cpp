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

QSqlQuery* DBRepository::getMatchesQuery() const
{
    QSqlQuery* query = new QSqlQuery;
    if(!query->exec(getMatchesSQLRequest())){
        QMessageBox::critical(nullptr, "Matches request to database error",
                              "There is a problem with sending request about matches information.");
        return nullptr;
    }
    else{
        return query;
    }

}

QString DBRepository::getMatchesSQLRequest() const
{
    return  "select gameid, team1, teamType1, finalscore, club.club_name as team2, team.name as teamType2, stadium.name as stadium,"
            "gameDate, tournament.name as tournName, tourn_stage.name as stage "
            "from club, stadium,"
            "(select game.id as gameid, club.club_name as team1, team.name as teamType1, game.final_score as finalscore,"
            "game.second_team as team2, game.starts_at as gameDate, game.stadium_id as stadiumid,"
            "game.tourn_id as tournId, game.stage_id as tournStageId "
            "from club, game, team, stadium "
            "where game.first_team=team.id and team.club_id=club.id and game.stadium_id=stadium.id) as subReq "
            "left join tournament on tournId=tournament.id "
            "left join tourn_stage on subReq.tournStageId=tourn_stage.id "
            "left join team on team2 = team.id "
            "where subReq.team2=team.id and team.club_id=club.id and stadiumid=stadium.id "
            "order by gameDate asc;";
}

void DBRepository::testPrint()
{
    QSqlQuery query;
    if(!query.exec(getMatchesSQLRequest())){
        qInfo() << "Bad request";
    }
    else{
        qInfo() << "good";
    }
    QSqlRecord rec = query.record();
    QString team1;
    QString team2;
    QString score;
    while(query.next()){
        team1 = query.value(rec.indexOf("team1")).toString();
        score = query.value(rec.indexOf("finalscore")).toString();
        team2 = query.value(rec.indexOf("team2")).toString();
        qInfo() << team1 << score << team2;
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
