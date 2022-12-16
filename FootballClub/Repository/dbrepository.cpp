/***************************************************************************
 *                                                                         *
 *   Copyright (C) 11.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "dbrepository.h"
#include "InfoNotes/DataWidgets/combobox.h"

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

QSqlQuery *DBRepository::getTournNamesQuery() const
{
    return getQuery(getTournNamesSQLRequest());
}

QSqlQuery *DBRepository::getStageNamesQuery() const
{
    return getQuery(getStageNamesSQLRequest());
}

QSqlQuery *DBRepository::getTeamTypeNamesQuery() const
{
    return getQuery(getTeamTypeNamesSQLRequest());
}

QSqlQuery *DBRepository::getClubNamesQuery() const
{
    return getQuery(getClubNamesSQLRequest());
}

QSqlQuery *DBRepository::getStadiumNamesQuery() const
{
    return getQuery(getStadiumNamesSQLRequest());
}

bool DBRepository::saveMatchData(const std::map<QString, TextField*>& fieldsMap)
{
    //todo!
}

int DBRepository::postMatchData(const std::map<QString, TextField *> &fieldsMap) //return inserted id
{
    QSqlQuery query;
    query.prepare(getMatchPostSQLRequest());

    ComboBox* stadiumClubComboBox = (ComboBox*)fieldsMap.find("stadium")->second;
    unsigned stadiumId = stadiumClubComboBox->getIdByValue(fieldsMap.find("stadium")->second->getText());

    ComboBox* firstClubComboBox = (ComboBox*)fieldsMap.find("team1")->second;
    unsigned stadiumId = firstClubComboBox->getIdByValue(fieldsMap.find("team1")->second->getText());

    ComboBox* secondClubComboBox = (ComboBox*)fieldsMap.find("team2")->second;
    unsigned stadiumId = secondClubComboBox->getIdByValue(fieldsMap.find("team2")->second->getText());

    ComboBox* stageClubComboBox = (ComboBox*)fieldsMap.find("stage")->second;
    unsigned stadiumId = stageClubComboBox->getIdByValue(fieldsMap.find("stage")->second->getText());

    ComboBox* tournamentComboBox = (ComboBox*)fieldsMap.find("tournament")->second;
    unsigned stadiumId = tournamentComboBox->getIdByValue(fieldsMap.find("tournament")->second->getText());
    //query.bindValue(":some_column_name", "FooBar");
//    query.exec();

    //qDebug() << "Last ID was:" << query.lastInsertId();
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

QString DBRepository::getTournNamesSQLRequest() const
{
    return "select id, name from tournament;";
}

QString DBRepository::getStageNamesSQLRequest() const
{
    return "select id, name from tourn_stage;";
}

QString DBRepository::getTeamTypeNamesSQLRequest() const
{
    return "select id, name from team_type;";
}

QString DBRepository::getClubNamesSQLRequest() const
{
    return "select id, club_name as name from club;";
}

QString DBRepository::getStadiumNamesSQLRequest() const
{
    return "select id, name from stadium;";
}

QString DBRepository::getMatchUpdateSQLRequest() const
{
    //"update game set s";
}

QString DBRepository::getMatchPostSQLRequest() const
{
    return "insert into game(stadium_id, first_team, second_team,"
           " final_score, stage_id, starts_at, tourn_id)"
           " values(:stadium_id, :first_team, :second_team, :final_score, "
           " :stage_id, :starts_at, :tourn_id);";
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
