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

QSqlQuery *DBRepository::getQuery(const QString request) const
{
    qInfo() << request;
    QSqlQuery* query = new QSqlQuery;
    if(!query->exec(request)){
        QMessageBox::critical(nullptr, "Query request to database error",
                              "There is a problem with sending request.");
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

bool DBRepository::saveData(const LABEL_TYPE type, const std::map<QString, TextField *> &fieldsMap, const unsigned id)
{
    switch (type) {
    case PLAYERS:
        return savePlayerData(fieldsMap, id);
    case COACHES:
        return saveManagerData(fieldsMap, id);
    case MATCHES:
        return saveMatchData(fieldsMap, id);
    case CLUB:
        break;

    default:
        break;
    }
}

int DBRepository::postData(const LABEL_TYPE type, const std::map<QString, TextField *> &fieldsMap)
{
    switch (type) {
    case PLAYERS:
        return postPlayerData(fieldsMap);
    case COACHES:
        return postManagerData(fieldsMap);
    case MATCHES:
        return postMatchData(fieldsMap);
    case CLUB:
        break;

    default:
        break;
    }
}

bool DBRepository::deleteData(const LABEL_TYPE type, const unsigned id)
{
    switch (type) {
    case PLAYERS:
        return deletePlayerData(id);
    case COACHES:
        return deleteManagerData(id);
        break;
    case MATCHES:
        return deleteMatchData(id);
    case CLUB:
        break;

    default:
        break;
    }
}




bool DBRepository::deletePlayerData(const unsigned id)
{
    QSqlQuery query;
    query.prepare(getPlayerDeleteSQLRequest());

    query.bindValue(":id", id);

    if(!query.exec()){
        QMessageBox::critical(nullptr, "Player request to database error",
                              "There is a problem with sending request about player information.");
        return false;
    }
    else{
        qInfo() << "Success request";
        return true;
    }
}

bool DBRepository::savePlayerData(const std::map<QString, TextField *> &fieldsMap, const unsigned id)
{
    int contractId;
    if(isNeedToUpdateContractId(fieldsMap)){
        contractId = postContractData(fieldsMap);
        if(contractId == -1){
            qInfo() << "Contract id failed";
            return false;
        }
    }
    else{
        QSqlQuery queryForContract;
        queryForContract.prepare(getContractIdByPlayerSQLRequest());
        queryForContract.bindValue(":id", id);
        if(!queryForContract.exec()){
            QMessageBox::critical(nullptr, "Matches request to database error",
                                  "There is a problem with sending request about matches information.");
            return false;
        }
        else{
            QSqlRecord record = queryForContract.record();
            qInfo() << "Good";
            queryForContract.next();
            contractId = queryForContract.value(record.indexOf("contract_id")).toInt();
        }
        qInfo() << "Contract id is: " << contractId;
        //contractId
    }

    QSqlQuery query;
    query.prepare(getPlayerUpdateSQLRequest());
    QString gameNumber = fieldsMap.find("gamenumber")->second->getText();
    QString playerName = fieldsMap.find("name")->second->getText();

    ComboBox* playerPosComboBox = (ComboBox*)fieldsMap.find("pos")->second;
    int playerPosId = playerPosComboBox->getIdByValue(fieldsMap.find("pos")->second->getText());
    if(playerPosId == -1){
        qInfo() << "Player pos id failed";
        return false;
    }

    QString birthday = fieldsMap.find("birthday")->second->getText();
    QString height = fieldsMap.find("height")->second->getText();
    QString weight = fieldsMap.find("weight")->second->getText();

    ComboBox* countryComboBox = (ComboBox*)fieldsMap.find("country")->second;
    int countryId = countryComboBox->getIdByValue(fieldsMap.find("country")->second->getText());
    if(countryId == -1){
        qInfo() << "country id failed";
        return false;
    }

    ComboBox* teamTypeComboBox = (ComboBox*)fieldsMap.find("teamtype")->second;
    int teamId = getTeamIdByClubIdAndTeamTypeId(PSG_CLUB_ID, teamTypeComboBox, fieldsMap);
    if(teamId == -1){
        qInfo() << "teamId failed";
        return false;
    }

    query.bindValue(":id", id);
    query.bindValue(":name", playerName);
    query.bindValue(":player_pos", playerPosId);
    query.bindValue(":height", height);
    query.bindValue(":team_id", teamId);
    query.bindValue(":contract", contractId);
    query.bindValue(":country", countryId);
    query.bindValue(":weight", weight);
    query.bindValue(":birthday", birthday);
    query.bindValue(":gamenumber", gameNumber);

    if(!query.exec()){
        QMessageBox::critical(nullptr, "Player request to database error",
                              "There is a problem with sending request about players information.");
        return false;
    }
    else{
        qInfo() << "Success request";
        return true;
    }
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


    ComboBox* teamTypeComboBox = (ComboBox*)fieldsMap.find("teamtype")->second;
    ComboBox* firstClubComboBox = (ComboBox*)fieldsMap.find("club1")->second;
    unsigned firstTeamId = getTeamIdByClubIdAndTeamTypeId(firstClubComboBox, teamTypeComboBox, fieldsMap, "club1");
    qInfo() << "First team id = " << firstTeamId;


    ComboBox* secondClubComboBox = (ComboBox*)fieldsMap.find("club2")->second;
    unsigned secondTeamId = getTeamIdByClubIdAndTeamTypeId(secondClubComboBox, teamTypeComboBox, fieldsMap, "club2");
    qInfo() << "Second team id = " << secondTeamId;

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

    ComboBox* firstClubComboBox = (ComboBox*)fieldsMap.find("club1")->second;
    ComboBox* teamTypeComboBox = (ComboBox*)fieldsMap.find("teamtype")->second;

    int firstTeamId = getTeamIdByClubIdAndTeamTypeId(firstClubComboBox, teamTypeComboBox, fieldsMap, "club1");
    if(firstTeamId == -1){
        qInfo() << "first team failed";
        return -1;
    }
    qInfo() << "Team1" << firstTeamId;
    ComboBox* secondClubComboBox = (ComboBox*)fieldsMap.find("club2")->second;
    int secondTeamId = getTeamIdByClubIdAndTeamTypeId(secondClubComboBox, teamTypeComboBox, fieldsMap, "club2");
    if(secondTeamId == -1){
        qInfo() << "second team failed";
        return -1;
    }
    qInfo() << "Team2" << secondTeamId;

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

int DBRepository::postPlayerData(const std::map<QString, TextField *> &fieldsMap)
{
    int contractId = postContractData(fieldsMap);
    if(contractId == -1){
        qInfo() << "Contract id failed";
        return -1;
    }

    QSqlQuery query;
    query.prepare(getPlayerPostSQLRequest());
    QString gameNumber = fieldsMap.find("gamenumber")->second->getText();
    QString playerName = fieldsMap.find("name")->second->getText();

    ComboBox* playerPosComboBox = (ComboBox*)fieldsMap.find("pos")->second;
    int playerPosId = playerPosComboBox->getIdByValue(fieldsMap.find("pos")->second->getText());
    if(playerPosId == -1){
        qInfo() << "Player pos id failed";
        return -1;
    }

    QString birthday = fieldsMap.find("birthday")->second->getText();
    QString height = fieldsMap.find("height")->second->getText();
    QString weight = fieldsMap.find("weight")->second->getText();

    ComboBox* countryComboBox = (ComboBox*)fieldsMap.find("country")->second;
    int countryId = countryComboBox->getIdByValue(fieldsMap.find("country")->second->getText());
    if(countryId == -1){
        qInfo() << "country id failed";
        return -1;
    }

    ComboBox* teamTypeComboBox = (ComboBox*)fieldsMap.find("teamtype")->second;
    int teamId = getTeamIdByClubIdAndTeamTypeId(PSG_CLUB_ID, teamTypeComboBox, fieldsMap);
    if(teamId == -1){
        qInfo() << "teamId failed";
        return -1;
    }

    query.bindValue(":name", playerName);
    query.bindValue(":player_pos", playerPosId);
    query.bindValue(":height", height);
    query.bindValue(":team_id", teamId);
    query.bindValue(":contract", contractId);
    query.bindValue(":country", countryId);
    query.bindValue(":weight", weight);
    query.bindValue(":birthday", birthday);
    query.bindValue(":gamenumber", gameNumber);

    if(!query.exec()){
        QMessageBox::critical(nullptr, "Player request to database error",
                              "There is a problem with sending request about players information.");
        return -1;
    }
    else{
        qInfo() << "Success request";
        return query.lastInsertId().toInt();
    }
}

int DBRepository::postContractData(const std::map<QString, TextField *> &fieldsMap)
{
    qInfo() << "postContractData";
    QSqlQuery query;
    query.prepare(getContractPostSQLRequest());

    QString beginAt = fieldsMap.find("inclubsince")->second->getText();
    QString endsAt = fieldsMap.find("leftfromclub")->second->getText();
    QString salaryValue = fieldsMap.find("yearsalary")->second->getText();


    query.bindValue(":begin", beginAt);
    query.bindValue(":end", endsAt);
    query.bindValue(":salary", salaryValue);
    query.bindValue(":club_id", PSG_CLUB_ID);


    if(!query.exec()){
        QMessageBox::critical(nullptr, "Contract request to database error",
                              "There is a problem with sending request about contract information.");
        return -1;
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
        return false;
    }
    else{
        qInfo() << "Success request";
        return true;
    }
}

int DBRepository::getTeamIdByClubIdAndTeamTypeId(ComboBox *clubBox, ComboBox *teamTypeBox,
                                                      const std::map<QString, TextField *> &fieldsMap, const QString& whichTeam) const
{
    unsigned clubId = clubBox->getIdByValue(fieldsMap.find(whichTeam)->second->getText());
    qInfo() << "Club id = " << clubId;

    unsigned teamTypeId = teamTypeBox->getIdByValue(fieldsMap.find("teamtype")->second->getText());
    qInfo() << "teamType id = " << teamTypeId;
    QSqlQuery queryForTeam;

    queryForTeam.prepare(getTeamIdByClubAndTeamTypeSQLRequest());
    queryForTeam.bindValue(":club_id", clubId);
    queryForTeam.bindValue(":team_type_id", teamTypeId);
    if(!queryForTeam.exec()){
        QMessageBox::critical(nullptr, "Matches request to database error",
                              "There is a problem with sending request about matches information.");

    }
    else{
        QSqlRecord record = queryForTeam.record();
        qInfo() << "Good";
        queryForTeam.next();
        return queryForTeam.value(record.indexOf("id")).toInt();
    }
    return -1;
}

int DBRepository::getTeamIdByClubIdAndTeamTypeId(const unsigned clubId, ComboBox *teamTypeBox,
                                                 const std::map<QString, TextField *> &fieldsMap) const
{
    unsigned teamTypeId = teamTypeBox->getIdByValue(fieldsMap.find("teamtype")->second->getText());
    qInfo() << "teamType id = " << teamTypeId;
    QSqlQuery queryForTeam;

    queryForTeam.prepare(getTeamIdByClubAndTeamTypeSQLRequest());
    queryForTeam.bindValue(":club_id", clubId);
    queryForTeam.bindValue(":team_type_id", teamTypeId);
    if(!queryForTeam.exec()){
        QMessageBox::critical(nullptr, "Team id request to database error",
                              "There is a problem with sending request about team id information.");
    }
    else{
        QSqlRecord record = queryForTeam.record();
        qInfo() << "Good";
        queryForTeam.next();
        return queryForTeam.value(record.indexOf("id")).toInt();
    }
    return -1;
}

bool DBRepository::isNeedToUpdateContractId(const std::map<QString, TextField *> &newValues)
{
    QString newClubInSince = newValues.find("inclubsince")->second->getText();
    QString newClubLeftFrom = newValues.find("leftfromclub")->second->getText();
    QString newSalary = newValues.find("yearsalary")->second->getText();

    QString prevClubInSince = newValues.find("inclubsincePREV")->second->getText();
    QString prevClubLeftFrom = newValues.find("leftfromclubPREV")->second->getText();
    QString prevSalary = newValues.find("yearsalaryPREV")->second->getText();
    if((newClubInSince == prevClubInSince) &&
       (newClubLeftFrom == prevClubLeftFrom) &&
        (newSalary == prevSalary)){
        return false;
    }
    return true;
}


QSqlQuery *DBRepository::getCountryNamesQuery() const
{
    return getQuery(getCountriesSQLRequest());
}


QSqlQuery *DBRepository::getPlayersQuery() const
{
    return getQuery(getPlayersSQLRequest());
}

QSqlQuery *DBRepository::getPlayerPositionNamesQuery() const
{
    return getQuery(getPlayerPositionNamesSQLRequest());
}



QSqlQuery *DBRepository::getManagersQuery() const
{
    return getQuery(getManagersSQLRequest());
}

QSqlQuery *DBRepository::getManagerTitlesQuery() const
{
    return getQuery(getManagerTitleNamesSQLRequest());
}

int DBRepository::postManagerData(const std::map<QString, TextField *> &fieldsMap)
{
    int contractId = postContractData(fieldsMap);
    if(contractId == -1){
        qInfo() << "Contract id failed";
        return -1;
    }

    QSqlQuery query;
    query.prepare(getManagerPostSQLRequest());
    ComboBox* titleComboBox = (ComboBox*)fieldsMap.find("title")->second;
    int postId = titleComboBox->getIdByValue(fieldsMap.find("title")->second->getText());
    if(postId == -1){
        qInfo() << "Title id failed";
        return -1;
    }

    ComboBox* teamTypeComboBox = (ComboBox*)fieldsMap.find("teamtype")->second;
    int teamId = getTeamIdByClubIdAndTeamTypeId(PSG_CLUB_ID, teamTypeComboBox, fieldsMap);
    if(teamId == -1){
        qInfo() << "teamId failed";
        return -1;
    }

    QString managerName = fieldsMap.find("name")->second->getText();

    QString birthday = fieldsMap.find("birthday")->second->getText();

    ComboBox* countryComboBox = (ComboBox*)fieldsMap.find("country")->second;
    int countryId = countryComboBox->getIdByValue(fieldsMap.find("country")->second->getText());
    if(countryId == -1){
        qInfo() << "country id failed";
        return -1;
    }

    query.bindValue(":name", managerName);
    query.bindValue(":team_id", teamId);
    query.bindValue(":post_id", postId);
    query.bindValue(":contract", contractId);
    query.bindValue(":country", countryId);
    query.bindValue(":birthday", birthday);


    if(!query.exec()){
        QMessageBox::critical(nullptr, "Manager request to database error",
                              "There is a problem with sending request about manager information.");
        return -1;
    }
    else{
        qInfo() << "Success request";
        return query.lastInsertId().toInt();
    }
}

bool DBRepository::saveManagerData(const std::map<QString, TextField *> &fieldsMap, const unsigned id)
{
    int contractId;
    if(isNeedToUpdateContractId(fieldsMap)){
        contractId = postContractData(fieldsMap);
        if(contractId == -1){
            qInfo() << "Contract id failed";
            return false;
        }
    }
    else{
        QSqlQuery queryForContract;
        queryForContract.prepare(getContractIdByManagerSQLRequest());
        queryForContract.bindValue(":id", id);
        if(!queryForContract.exec()){
            QMessageBox::critical(nullptr, "Manager request to database error",
                                  "There is a problem with sending request about manager information.");
            return false;
        }
        else{
            QSqlRecord record = queryForContract.record();
            qInfo() << "Good";
            queryForContract.next();
            contractId = queryForContract.value(record.indexOf("contract_id")).toInt();
        }
        qInfo() << "Contract id is: " << contractId;
    }

    QSqlQuery query;
    query.prepare(getManagerUpdateSQLRequest());

    ComboBox* titleComboBox = (ComboBox*)fieldsMap.find("title")->second;
    int postId = titleComboBox->getIdByValue(fieldsMap.find("title")->second->getText());
    if(postId == -1){
        qInfo() << "Title id failed";
        return false;
    }

    ComboBox* teamTypeComboBox = (ComboBox*)fieldsMap.find("teamtype")->second;
    int teamId = getTeamIdByClubIdAndTeamTypeId(PSG_CLUB_ID, teamTypeComboBox, fieldsMap);
    if(teamId == -1){
        qInfo() << "teamId failed";
        return false;
    }

    QString managerName = fieldsMap.find("name")->second->getText();

    QString birthday = fieldsMap.find("birthday")->second->getText();

    ComboBox* countryComboBox = (ComboBox*)fieldsMap.find("country")->second;
    int countryId = countryComboBox->getIdByValue(fieldsMap.find("country")->second->getText());
    if(countryId == -1){
        qInfo() << "country id failed";
        return false;
    }


    query.bindValue(":id", id);
    query.bindValue(":name", managerName);
    query.bindValue(":team_id", teamId);
    query.bindValue(":post_id", postId);
    query.bindValue(":contract", contractId);
    query.bindValue(":country_id", countryId);
    query.bindValue(":birthday", birthday);

    if(!query.exec()){
        QMessageBox::critical(nullptr, "Manager request to database error",
                              "There is a problem with sending SAVE request about manager information.");
        return false;
    }
    else{
        qInfo() << "Success request";
        return true;
    }
}

bool DBRepository::deleteManagerData(const unsigned id)
{
    QSqlQuery query;
    query.prepare(getManagerDeleteSQLRequest());

    query.bindValue(":id", id);

    if(!query.exec()){
        QMessageBox::critical(nullptr, "Manager request to database error",
                              "There is a problem with sending request DELETE about manager information.");
        return false;
    }
    else{
        qInfo() << "Success request";
        return true;
    }
}





QString DBRepository::getMatchesSQLRequest() const
{
    return  "select gameid, club1, teamType1, finalscore, club.club_name as club2,"
            "team_type.name as teamType2, stadium.name as stadium,"
            "gameDate, tournament.name as tournName, tourn_stage.name as stage "
            "from club, stadium,"
            "(select game.id as gameid, club.club_name as club1, club.id as team1id,"
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
            "where subReq.team2=team.id and team.club_id=club.id and stadiumid=stadium.id and (subReq.team1id=1 or club.id=1) "
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

QString DBRepository::getPlayerPositionNamesSQLRequest() const
{
    return "select id, pos as name from player_pos;";
}

QString DBRepository::getCountriesSQLRequest() const
{
    return "select id, name from country;";
}

QString DBRepository::getPlayerUpdateSQLRequest() const
{
    return "update player set name=:name, position_id=:player_pos, height=:height,"
           "team_id=:team_id, contract_id=:contract, born_country_id=:country, "
           "weight=:weight, birthday=:birthday, number=:gameNumber "
           "where id=:id;";
}



QString DBRepository::getPlayerPostSQLRequest() const
{
    return "insert into player(name, position_id, "
           "height, team_id, contract_id, born_country_id,"
           " weight, birthday, number) "
           "values(:name, :player_pos, :height, :team_id, :contract, :country, :weight,"
           ":birthday, :gamenumber);";
}



QString DBRepository::getContractIdByPlayerSQLRequest() const
{
    return "select contract_id from player where id=:id;";
}

QString DBRepository::getContractIdByManagerSQLRequest() const
{
    return "select contract_id from manager where id=:id;";
}

QString DBRepository::getManagerUpdateSQLRequest() const
{
    return "update manager set name=:name, team_id=:team_id, post_id=:post_id, "
           "contract_id=:contract, born_country_id=:country_id, birthday=:birthday "
           "where id=:id;";
}

QString DBRepository::getManagerDeleteSQLRequest() const
{
    return "delete from manager where id=:id;";
}

QString DBRepository::getManagersSQLRequest() const
{
    return "select manager.id, manager.name as name, manager.birthday as birthday, country.name as borncountry,"
           "post.title as title, football_contract.begin_at as inclubsince,"
           "football_contract.end_at as leftfromclub, football_contract.salary_per_year as yearsalary,"
           "team_type.name as teamtype "
           "from manager, team, club, country, post, football_contract, team_type "
           "where manager.post_id=post.id and manager.team_id=team.id and "
           "manager.born_country_id=country.id and team_type.id =manager.team_id and "
           "manager.contract_id=football_contract.id and club.id=1;";
}

QString DBRepository::getManagerTitleNamesSQLRequest() const
{
    return "select id, title from post;";
}

QString DBRepository::getManagerPostSQLRequest() const
{
    return "insert into manager(name, team_id, post_id, contract_id, "
           "born_country_id, birthday) values(:name, :team_id, :post_id, :contract,"
           ":country, :birthday);";
}





QString DBRepository::getPlayerDeleteSQLRequest() const
{
    return "delete from player where id=:id;";
}

QString DBRepository::getContractPostSQLRequest() const
{
    return "insert into football_contract(begin_at, end_at, salary_per_year, club_id) "
           "values(:begin, :end, :salary, :club_id);";
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

QString DBRepository::getTeamIdByClubAndTeamTypeSQLRequest() const
{
    return "select id from team where club_id=:club_id and team_type_id=:team_type_id " ;
}

QString DBRepository::getPlayersSQLRequest() const
{
    return  "select player.id, player.name, player_pos.pos as pos, club.club_name as club,"
            "team_type.name as teamtype,"
            "player.height as height, player.weight as weight, country.name as country,"
            "player.birthday as birthday, football_contract.salary_per_year as yearsalary, player.number as gamenumber,"
            " football_contract.begin_at as inclubsince,"
            "football_contract.end_at as leftfromclub "
            "from player, club, team, country, player_pos, football_contract, team_type "
            "where player.team_id=team.id and team.club_id=club.id and "
            "player.born_country_id=country.id and player.position_id=player_pos.id "
            "and football_contract.id = player.contract_id and player.team_id = team_type.id and club.id=1 "
            "order by yearsalary desc;";

}


