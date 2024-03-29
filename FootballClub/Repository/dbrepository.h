/***************************************************************************
 *                                                                         *
 *   Copyright (C) 11.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef DBREPOSITORY_H
#define DBREPOSITORY_H
#include "Enums/Enums.h"
#include "InfoNotes/DataWidgets/combobox.h"
#include "InfoNotes/Notes/BaseNote.h"
#pragma once
#include "InfoNotes/DataWidgets/textfield.h"
#include "DataBase/database.h"
#include <map>
#define PSG_CLUB_ID 1

class DBRepository
{//class for database requests
public:
    DBRepository();
    ~DBRepository();

private:
    //DELETE THIS FRIEND MANAGER CLASS AND MADE BETTER PUBLIC/PRIVATE DIFFERENCE
    //GET QUERIES
    QSqlQuery* getQuery(const QString request) const;

    //Matches
    QSqlQuery* getMatchesQuery(const QString& searchDataText) const;
    QSqlQuery* getTournNamesQuery() const;
    QSqlQuery* getStageNamesQuery() const;
    QSqlQuery* getTeamTypeNamesQuery() const;
    QSqlQuery* getClubNamesQuery() const;
    QSqlQuery* getStadiumNamesQuery() const;
    QSqlQuery* getCountryNamesQuery() const;

    bool saveData(const LABEL_TYPE type, const std::map<QString, TextField*>& fieldsMap,
                  const unsigned id, const REQUEST_TYPE reqType=GET);
    int postData(const LABEL_TYPE type, const std::map<QString, TextField*>& fieldsMap);
    bool deleteData(const LABEL_TYPE type, const unsigned id);


    bool saveMatchData(const std::map<QString, TextField*>& fieldsMap, const unsigned id);
    int postMatchData(const std::map<QString, TextField*>& fieldsMap);

    bool deleteMatchData(const unsigned id);
    int getTeamIdByClubIdAndTeamTypeId(ComboBox* clubBox, ComboBox* teamTypeBox,
                                            const std::map<QString, TextField*>& fieldsMap, const QString& whichTeam) const;
    int getTeamIdByClubIdAndTeamTypeId(const unsigned club_id, ComboBox* teamTypeBox,
                                            const std::map<QString, TextField*>& fieldsMap) const;




    //Players
    int postContractData(const std::map<QString, TextField*>& fieldsMap);
    int postPlayerData(const std::map<QString, TextField*>& fieldsMap);
    QSqlQuery* getPlayersQuery(const QString& searchDataText) const;
    QSqlQuery* getPlayerPositionNamesQuery() const;

    bool deletePlayerData(const unsigned id);
    bool savePlayerData(const std::map<QString, TextField*>& fieldsMap, const unsigned id);

    bool isNeedToUpdateContractId(const std::map<QString, TextField*>& newValues);

    int getContractIdByPersonId(const unsigned playerId, const LABEL_TYPE whoseIdType);

    //Managers
    QSqlQuery* getManagersQuery(const QString& searchDataText) const;
    QSqlQuery* getManagerTitlesQuery() const;
    int postManagerData(const std::map<QString, TextField*>& fieldsMap);
    bool saveManagerData(const std::map<QString, TextField*>& fieldsMap,
                         const unsigned id, const REQUEST_TYPE reqType);
    bool deleteManagerData(const unsigned id);

    bool isMainCoachInPSGExist(const unsigned team_id);

    bool deleteContractById(const unsigned id);
    QSqlQuery* getMainCoachOfPSG();

    //Club
    QSqlQuery* getClubQuery() const;


    //SQL REQUESTS
    QString getMatchesSQLRequest() const;
    QString getMatchUpdateSQLRequest() const;
    QString getMatchPostSQLRequest() const;
    QString getMatchDeleteSQLRequest() const;

    QString getTournNamesSQLRequest() const;
    QString getStageNamesSQLRequest() const;
    QString getTeamTypeNamesSQLRequest() const;
    QString getClubNamesSQLRequest() const;
    QString getStadiumNamesSQLRequest() const;
    QString getTeamIdByClubAndTeamTypeSQLRequest() const;

    QString getPlayersSQLRequest() const;
    QString getPlayerUpdateSQLRequest() const;
    QString getPlayerPostSQLRequest() const;
    QString getPlayerDeleteSQLRequest() const;

    QString getPlayerPositionNamesSQLRequest() const;
    QString getCountriesSQLRequest() const;

    QString getContractPostSQLRequest() const;
    QString getContractDeleteSQLRequest() const;
    QString getContractIdByPlayerSQLRequest()const;

    QString getManagersSQLRequest() const;

    QString getManagerTitleNamesSQLRequest() const;
    QString getManagerPostSQLRequest() const;
    QString getManagerUpdateSQLRequest() const;
    QString getManagerDeleteSQLRequest() const;
    QString getMainCoachOfPSGSQLRequest() const;
    QString getContractIdByManagerSQLRequest() const;

    QString getClubSQLRequest() const;

    DataBase* database = nullptr;
    bool createConnection();
    friend class WindowManager;
};

#endif // DBREPOSITORY_H
