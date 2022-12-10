/***************************************************************************
 *                                                                         *
 *   Copyright (C) 10.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "database.h"

DataBase::DataBase()
{
    database = new QSqlDatabase();
}

DataBase::~DataBase()
{
    database->close();
    database->removeDatabase(databaseName);
    if(database->lastError().text().isEmpty()){
        qInfo() << "Database was sucessfully closed.";
    }
    else{
        qInfo() << "Database close error:" << database->lastError().text();
    }
    delete database;
}

bool DataBase::createConnection(const QString &databaseType, const QString &dbName, const QString &userName, const QString &password)
{
    *database = QSqlDatabase::addDatabase(databaseType);
    database->setDatabaseName(dbName);
    databaseName = dbName;
    database->setUserName(userName);
    database->setPassword(password);

    if(!database->open()){
        qInfo() << "DataBase openning error." << database->lastError().text();
        return false;
    }
    else{
        qInfo() << "DataBase was sucessfully opened.";
        return true;
    }
}
