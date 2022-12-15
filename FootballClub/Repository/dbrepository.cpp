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

QSqlQuery *DBRepository::getQuery(const QString request) const
{
    qInfo() << request;
    QSqlQuery* query = new QSqlQuery;
    if(!query->exec(request)){
        QMessageBox::critical(nullptr, "Matches request to database error",
                              "There is a problem with sending request about matches information.");
        return nullptr;
    }
    else{
        qInfo() << "Success request";
        return query;
    }
}

QSqlQuery* DBRepository::getMatchesQuery() const
{
    return getQuery(getMatchesSQLRequest());
}

QSqlQuery *DBRepository::getMatchTournamentsQuery() const
{
    return getQuery(getMatchTournsSQLRequest());
}

QSqlQuery *DBRepository::getMatchStagesQuery() const
{
    return getQuery(getMatchStagesSQLRequest());
}

QSqlQuery *DBRepository::getMatchTeamTypesQuery() const
{
    return getQuery(getMatchTeamTypesSQLRequest());
}

QSqlQuery *DBRepository::getMatchClubsQuery() const
{
    return getQuery(getMatchClubsSQLRequest());
}










QString DBRepository::getMatchesSQLRequest() const
{
    return  "select gameid, team1, teamType1, finalscore, club.club_name as team2,"
            "team_type.name as teamType2, stadium.name as stadium,"
            "gameDate, tournament.name as tournName, tourn_stage.name as stage "
            "from club, stadium,"
            "(select game.id as gameid, club.club_name as team1, club.id as team1id,"
            " team_type.name as teamType1, game.final_score as finalscore,"
            "game.second_team as team2, game.starts_at as gameDate, game.stadium_id as stadiumid,"
            "game.tourn_id as tournId, game.stage_id as tournStageId "
            "from club, game, team, stadium, team_type "
            "where game.first_team=team.id and team.club_id=club.id "
            "and game.stadium_id=stadium.id and team.team_type_id=team_type.id) as subReq "
            "left join tournament on tournId=tournament.id "
            "left join tourn_stage on subReq.tournStageId=tourn_stage.id "
            "left join team on team2 = team.id "
            "left join team_type on team_type.id = team.team_type_id "
            "where subReq.team2=team.id and team.club_id=club.id and "
            "stadiumid=stadium.id and (subReq.team1id=1 or club.id=1) "
            "order by gameDate asc;";
}

QString DBRepository::getMatchTournsSQLRequest() const
{
    return "select name from tournament;";
}

QString DBRepository::getMatchStagesSQLRequest() const
{
    return "select name from tourn_stage;";
}

QString DBRepository::getMatchTeamTypesSQLRequest() const
{
    return "select name from team_type;";
}

QString DBRepository::getMatchClubsSQLRequest() const
{
    return "select club_name as name from club;";
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
