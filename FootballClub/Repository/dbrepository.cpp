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

bool DBRepository::saveMatchData(const std::map<QString, TextField*>& fieldsMap, const unsigned id)
{
    qInfo() << "curr note id is : " << id;
    if(id <= 0){
        return false;
    }
    QSqlQuery query;
    query.prepare(getMatchUpdateSQLRequest());

    ComboBox* stadiumClubComboBox = (ComboBox*)fieldsMap.find("stadium")->second;
    unsigned stadiumId = stadiumClubComboBox->getIdByValue(fieldsMap.find("stadium")->second->getText());

    ComboBox* firstClubComboBox = (ComboBox*)fieldsMap.find("team1")->second;
    unsigned firstTeamId = firstClubComboBox->getIdByValue(fieldsMap.find("team1")->second->getText());

    ComboBox* secondClubComboBox = (ComboBox*)fieldsMap.find("team2")->second;
    unsigned secondTeamId = secondClubComboBox->getIdByValue(fieldsMap.find("team2")->second->getText());

    QString finalScore = fieldsMap.find("finalscore")->second->getText();

    ComboBox* stageClubComboBox = (ComboBox*)fieldsMap.find("stage")->second;
    unsigned stageId = stageClubComboBox->getIdByValue(fieldsMap.find("stage")->second->getText());

    QString gameDate = fieldsMap.find("gameDate")->second->getText();

    ComboBox* tournamentComboBox = (ComboBox*)fieldsMap.find("tournament")->second;
    unsigned tournId = tournamentComboBox->getIdByValue(fieldsMap.find("tournament")->second->getText());


    query.bindValue(":id", id);
    query.bindValue(":stadium_id", stadiumId);
    query.bindValue(":first_team", firstTeamId);
    query.bindValue(":second_team", secondTeamId);
    query.bindValue(":final_score", finalScore);
    query.bindValue(":stage_id", stageId);
    query.bindValue(":starts_at", gameDate);
    query.bindValue(":tourn_id", tournId);

    if(!query.exec()){
        QMessageBox::critical(nullptr, "Matches request to database error",
                              "There is a problem with sending request about matches information.");
        return false;
    }
    else{
        qInfo() << "Success request";
        return true;
    }
}

int DBRepository::postMatchData(const std::map<QString, TextField *> &fieldsMap) //return inserted id
{
    QSqlQuery query;
    query.prepare(getMatchPostSQLRequest());

    ComboBox* stadiumClubComboBox = (ComboBox*)fieldsMap.find("stadium")->second;
    unsigned stadiumId = stadiumClubComboBox->getIdByValue(fieldsMap.find("stadium")->second->getText());

    ComboBox* firstClubComboBox = (ComboBox*)fieldsMap.find("team1")->second;
    unsigned firstTeamId = firstClubComboBox->getIdByValue(fieldsMap.find("team1")->second->getText());

    ComboBox* secondClubComboBox = (ComboBox*)fieldsMap.find("team2")->second;
    unsigned secondTeamId = secondClubComboBox->getIdByValue(fieldsMap.find("team2")->second->getText());

    QString finalScore = fieldsMap.find("finalscore")->second->getText();

    ComboBox* stageClubComboBox = (ComboBox*)fieldsMap.find("stage")->second;
    unsigned stageId = stageClubComboBox->getIdByValue(fieldsMap.find("stage")->second->getText());

    QString gameDate = fieldsMap.find("gameDate")->second->getText();

    ComboBox* tournamentComboBox = (ComboBox*)fieldsMap.find("tournament")->second;
    unsigned tournId = tournamentComboBox->getIdByValue(fieldsMap.find("tournament")->second->getText());


    query.bindValue(":stadium_id", stadiumId);
    query.bindValue(":first_team", firstTeamId);
    query.bindValue(":second_team", secondTeamId);
    query.bindValue(":final_score", finalScore);
    query.bindValue(":stage_id", stageId);
    query.bindValue(":starts_at", gameDate);
    query.bindValue(":tourn_id", tournId);

    if(!query.exec()){
        QMessageBox::critical(nullptr, "Matches request to database error",
                              "There is a problem with sending request about matches information.");
        return 0;
    }
    else{
        qInfo() << "Success request";
        return query.lastInsertId().toInt();
    }
}

bool DBRepository::deleteMatchData(const unsigned id)
{
    QSqlQuery query;
    query.prepare(getMatchDeleteSQLRequest());

    query.bindValue(":id", id);

    if(!query.exec()){
        QMessageBox::critical(nullptr, "Matches request to database error",
                              "There is a problem with sending request about matches information.");
        return 0;
    }
    else{
        qInfo() << "Success request";
        return query.lastInsertId().toInt();
    }
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
    return "update game set stadium_id=:stadium_id, first_team=:first_team, "
           "second_team=:second_team, final_score=:final_score, "
           "stage_id=:stage_id, starts_at=:starts_at, tourn_id=:tourn_id "
           "where id=:id;";
}

QString DBRepository::getMatchPostSQLRequest() const
{
    return "insert into game(stadium_id, first_team, second_team,"
           " final_score, stage_id, starts_at, tourn_id)"
           " values(:stadium_id, :first_team, :second_team, :final_score, "
           " :stage_id, :starts_at, :tourn_id);";
}

QString DBRepository::getMatchDeleteSQLRequest() const
{
    return "delete from game where id=:id;";
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
