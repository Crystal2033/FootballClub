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

QSqlQuery* DBRepository::getMatchesQuery(const QString& searchDataText) const
{

    QSqlQuery* queryMatches = new QSqlQuery;

    queryMatches->prepare(getMatchesSQLRequest());
    queryMatches->bindValue(":partOfTeamName", searchDataText);

    if(!queryMatches->exec()){
        QMessageBox::critical(nullptr, "Get matches error",
                              "There is a problem with sending request about matches.");
        return nullptr;
    }
    else{
        qInfo() << "Success request";
        return queryMatches;
    }
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

bool DBRepository::saveData(const LABEL_TYPE type, const std::map<QString, TextField *> &fieldsMap,
                            const unsigned id, const REQUEST_TYPE reqType)
{
    switch (type) {
    case PLAYERS:
        return savePlayerData(fieldsMap, id);
    case COACHES:
        return saveManagerData(fieldsMap, id, reqType);
    case MATCHES:
        return saveMatchData(fieldsMap, id);
    case CLUB:
        break;

    default:
        break;
    }
    return false;
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
    qInfo() << id;
    QSqlQuery query;
    //QSQL can do only update, select, insert, delete...
    QString procedureRequest = "call deleteplayer(" + QString::number(id) + ");";

    if(!query.exec(procedureRequest)){
        QMessageBox::critical(nullptr, "Player request to database error",
                              "There is a problem with deleting player information.");
        qInfo() << query.lastError();
        return false;
    }
    else{
        qInfo() << "Success request";
        return true;
    }
}

bool DBRepository::savePlayerData(const std::map<QString, TextField *> &fieldsMap, const unsigned id)
{
    int newContractId;
    int oldContractId = getContractIdByPersonId(id, PLAYERS);

    if(oldContractId == -1){
        QMessageBox::critical(nullptr, "Request to database error",
                              "Player contract id from database is wrong.");
        return false;
    }

    if(isNeedToUpdateContractId(fieldsMap)){
        newContractId = postContractData(fieldsMap);
        if(newContractId == -1){
            qInfo() << "Contract id failed";
            return false;
        }

    }
    else{
        newContractId = oldContractId;
    }

    QSqlQuery query;
    query.prepare(getPlayerUpdateSQLRequest());
    int gameNumber = fieldsMap.find("gamenumber")->second->getText().toInt();
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

    qInfo() << "player game number" << gameNumber;
    query.bindValue(":id", id);
    query.bindValue(":name", playerName);
    query.bindValue(":player_pos", playerPosId);
    query.bindValue(":height", height);
    query.bindValue(":team_id", teamId);
    query.bindValue(":contract", newContractId);
    query.bindValue(":country", countryId);
    query.bindValue(":weight", weight);
    query.bindValue(":birthday", birthday);
    query.bindValue(":gameNumber", gameNumber);

    if(!query.exec()){
        QMessageBox::critical(nullptr, "Player request to database error",
                              "There is a problem with sending request about players information.");
        return false;
    }
    else{
        qInfo() << "Success request";
        if(newContractId != oldContractId){
            if(!deleteContractById(oldContractId)){
                QMessageBox::critical(nullptr, "Request to database error",
                                      "There is a problem with deleting contract from player.");
            }
        }
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
    ComboBox* secondClubComboBox = (ComboBox*)fieldsMap.find("club2")->second;
    if(firstClubComboBox->getText() == secondClubComboBox->getText()){
        QMessageBox::warning(nullptr, "Teams are the same error.", "You have to choose different teams");
        return false;
    }
    unsigned firstTeamId = getTeamIdByClubIdAndTeamTypeId(firstClubComboBox, teamTypeComboBox, fieldsMap, "club1");
    qInfo() << "First team id = " << firstTeamId;



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
    ComboBox* secondClubComboBox = (ComboBox*)fieldsMap.find("club2")->second;
    if(firstClubComboBox->getText() == secondClubComboBox->getText()){
        QMessageBox::warning(nullptr, "Teams are the same error.", "You have to choose different teams");
        return false;
    }

    ComboBox* teamTypeComboBox = (ComboBox*)fieldsMap.find("teamtype")->second;

    int firstTeamId = getTeamIdByClubIdAndTeamTypeId(firstClubComboBox, teamTypeComboBox, fieldsMap, "club1");
    if(firstTeamId == -1){
        qInfo() << "first team failed";
        return -1;
    }
    qInfo() << "Team1" << firstTeamId;

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
    int gameNumber = fieldsMap.find("gamenumber")->second->getText().toInt();

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
    query.bindValue(":gameNumber", gameNumber);

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

int DBRepository::getContractIdByPersonId(const unsigned int personId, const LABEL_TYPE whoseIdType)
{
    int contractId;
    QSqlQuery queryForContract;
    if(whoseIdType == PLAYERS){
        queryForContract.prepare(getContractIdByPlayerSQLRequest());
    }
    else if(whoseIdType == COACHES){
        queryForContract.prepare(getContractIdByManagerSQLRequest());
    }

    queryForContract.bindValue(":id", personId);
    if(!queryForContract.exec()){
        QMessageBox::critical(nullptr, "Request to database error",
                              "There is a problem with sending request with get contract id.");
        return -1;
    }
    else{
        QSqlRecord record = queryForContract.record();
        qInfo() << "Good";
        queryForContract.next();
        contractId = queryForContract.value(record.indexOf("contract_id")).toInt();
    }
    qInfo() << "Contract id is: " << contractId;
    return contractId;
}


QSqlQuery *DBRepository::getCountryNamesQuery() const
{
    return getQuery(getCountriesSQLRequest());
}


QSqlQuery *DBRepository::getPlayersQuery(const QString& searchDataText) const
{
    QSqlQuery* queryPlayers = new QSqlQuery;

    queryPlayers->prepare(getPlayersSQLRequest());
    queryPlayers->bindValue(":partOfName", searchDataText);

    if(!queryPlayers->exec()){
        QMessageBox::critical(nullptr, "Get players error",
                              "There is a problem with sending request about players.");
        return nullptr;
    }
    else{
        qInfo() << "Success request";
        return queryPlayers;
    }
}

QSqlQuery *DBRepository::getPlayerPositionNamesQuery() const
{
    return getQuery(getPlayerPositionNamesSQLRequest());
}


QSqlQuery *DBRepository::getClubQuery() const
{
    return getQuery(getClubSQLRequest());
}


QSqlQuery *DBRepository::getManagersQuery(const QString& searchDataText) const
{

    QSqlQuery* queryManagers = new QSqlQuery;

    queryManagers->prepare(getManagersSQLRequest());
    queryManagers->bindValue(":partOfName", searchDataText);

    if(!queryManagers->exec()){
        QMessageBox::critical(nullptr, "Get managers error",
                              "There is a problem with sending request about managers.");
        return nullptr;
    }
    else{
        qInfo() << "Success request";
        return queryManagers;
    }
}

QSqlQuery *DBRepository::getManagerTitlesQuery() const
{
    return getQuery(getManagerTitleNamesSQLRequest());
}

int DBRepository::postManagerData(const std::map<QString, TextField *> &fieldsMap)
{
    ComboBox* teamTypeComboBox = (ComboBox*)fieldsMap.find("teamtype")->second;
    int teamId = getTeamIdByClubIdAndTeamTypeId(PSG_CLUB_ID, teamTypeComboBox, fieldsMap);
    if(teamId == -1){
        qInfo() << "teamId failed";
        return -1;
    }

    ComboBox* titleComboBox = (ComboBox*)fieldsMap.find("title")->second;
    int postId = titleComboBox->getIdByValue(fieldsMap.find("title")->second->getText());
    if(postId == -1){
        qInfo() << "Title id failed";
        return false;
    }

    if(fieldsMap.find("title")->second->getText() == "Main coach"){// equals postId == 6
        if(isMainCoachInPSGExist(teamId)){
            QMessageBox::critical(nullptr, "Manager request to database error",
                                  "Main coach of PSG already exists.");
            return -1;
        }
    }

    int contractId = postContractData(fieldsMap);
    if(contractId == -1){
        qInfo() << "Contract id failed";
        return -1;
    }

    QSqlQuery query;
    query.prepare(getManagerPostSQLRequest());

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

bool DBRepository::saveManagerData(const std::map<QString, TextField *> &fieldsMap,
                                   const unsigned id, const REQUEST_TYPE reqType)
{

    ComboBox* teamTypeComboBox = (ComboBox*)fieldsMap.find("teamtype")->second;
    int teamId = getTeamIdByClubIdAndTeamTypeId(PSG_CLUB_ID, teamTypeComboBox, fieldsMap);
    if(teamId == -1){
        qInfo() << "teamId failed";
        return false;
    }

    ComboBox* titleComboBox = (ComboBox*)fieldsMap.find("title")->second;
    int postId = titleComboBox->getIdByValue(fieldsMap.find("title")->second->getText());
    if(postId == -1){
        qInfo() << "Title id failed";
        return false;
    }

    if(reqType != POST){// If post than it wont work. Because we added new note with Main coach and
                        //again checking after click on "Save"
        if(fieldsMap.find("title")->second->getText() == "Main coach"){// equals postId == 6
            if(isMainCoachInPSGExist(teamId)){
                QMessageBox::critical(nullptr, "Manager request to database error",
                                      "Main coach of PSG already exists.");
                return false;
            }
        }
    }



    int newContractId;
    int oldContractId = getContractIdByPersonId(id, COACHES);

    if(oldContractId == -1){
        QMessageBox::critical(nullptr, "Request to database error",
                              "Player contract id from database is wrong.");
        return false;
    }


    if(isNeedToUpdateContractId(fieldsMap)){
        newContractId = postContractData(fieldsMap);
        if(newContractId == -1){
            qInfo() << "Contract id failed";
            return false;
        }
    }
    else{
        newContractId = oldContractId;
    }

    QSqlQuery query;
    query.prepare(getManagerUpdateSQLRequest());





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
    query.bindValue(":contract", newContractId);
    query.bindValue(":country_id", countryId);
    query.bindValue(":birthday", birthday);

    if(!query.exec()){
        QMessageBox::critical(nullptr, "Manager request to database error",
                              "There is a problem with sending SAVE request about manager information.");
        return false;
    }
    else{
        qInfo() << "Success request";
        if(newContractId != oldContractId){
            if(!deleteContractById(oldContractId)){
                QMessageBox::critical(nullptr, "Request to database error",
                                      "There is a problem with deleting contract from player.");
            }
        }
        return true;
    }
}

bool DBRepository::deleteManagerData(const unsigned id)
{
    qInfo() << id;
    QSqlQuery query;
    //QSQL can do only update, select, insert, delete...
    QString procedureRequest = "call deletemanager(" + QString::number(id) + ");";

    if(!query.exec(procedureRequest)){
        QMessageBox::critical(nullptr, "Manager request to database error",
                              "There is a problem with deleting manager information.");
        qInfo() << query.lastError();
        return false;
    }
    else{
        qInfo() << "Success request";
        return true;
    }
}

bool DBRepository::isMainCoachInPSGExist(const unsigned int team_id)
{
    QSqlQuery query;
    query.prepare(getMainCoachOfPSGSQLRequest());

    query.bindValue(":team_id", team_id);
    query.bindValue(":post_id", 6);

    if(!query.exec()){
        QMessageBox::critical(nullptr, "Contract request to database error",
                              "There is a problem with sending request DELETE contract.");
        return false;
    }
    else{
        qInfo() << "Success request";

    }

    if(query.size() == 1){
        return true;
    }
    else{
        return false;
    }
}


bool DBRepository::deleteContractById(const unsigned int id)
{
    QSqlQuery query;
    query.prepare(getContractDeleteSQLRequest());

    query.bindValue(":id", id);

    if(!query.exec()){
        QMessageBox::critical(nullptr, "Contract request to database error",
                              "There is a problem with sending request DELETE contract.");
        return false;
    }
    else{
        qInfo() << "Success request";
        return true;
    }
}

QSqlQuery *DBRepository::getMainCoachOfPSG()
{
    return getQuery(getMainCoachOfPSGSQLRequest());
}

QString DBRepository::getMatchesSQLRequest() const
{
    return  "select * from searchmatch(:partOfTeamName);";
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

QString DBRepository::getClubSQLRequest() const
{
    return "select created_at from club where id=1;";
}

QString DBRepository::getContractDeleteSQLRequest() const
{
    return "delete from football_contract where id=:id;";
}

QString DBRepository::getMainCoachOfPSGSQLRequest() const
{ //6 --Main coach 1 -- PSG
    return "select name from manager where team_id=:team_id and post_id=:post_id;";
}

QString DBRepository::getManagersSQLRequest() const
{
    return "select * from searchmanager(:partOfName);";
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
    return "call deleteplayer(:id);";
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
    return  "select * from searchplayer(:partOfName);";

}


