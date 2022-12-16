/***************************************************************************
 *                                                                         *
 *   Copyright (C) 11.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef DBREPOSITORY_H
#define DBREPOSITORY_H
#pragma once
#include "InfoNotes/DataWidgets/textfield.h"
#include "DataBase/database.h"
#include <map>

class DBRepository
{//class for database requests
public:
    DBRepository();
    ~DBRepository();

private:
    QSqlQuery* getQuery(const QString request) const;
    //GET QUERIES
    QSqlQuery* getMatchesQuery() const;
    QSqlQuery* getTournNamesQuery() const;
    QSqlQuery* getStageNamesQuery() const;
    QSqlQuery* getTeamTypeNamesQuery() const;
    QSqlQuery* getClubNamesQuery() const;
    QSqlQuery* getStadiumNamesQuery() const;
    bool saveMatchData(const std::map<QString, TextField*>& fieldsMap, const unsigned id);
    int postMatchData(const std::map<QString, TextField*>& fieldsMap);






    //SQL REQUESTS
    QString getMatchesSQLRequest() const;
    QString getTournNamesSQLRequest() const;
    QString getStageNamesSQLRequest() const;
    QString getTeamTypeNamesSQLRequest() const;
    QString getClubNamesSQLRequest() const;
    QString getStadiumNamesSQLRequest() const;
    QString getMatchUpdateSQLRequest() const;
    QString getMatchPostSQLRequest() const;





    void testPrint();
    DataBase* database = nullptr;
    bool createConnection();
    friend class WindowManager;
};

#endif // DBREPOSITORY_H
