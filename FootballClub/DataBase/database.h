/***************************************************************************
 *                                                                         *
 *   Copyright (C) 10.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>

class DataBase
{
private:
    QSqlDatabase* database = nullptr;
    QString databaseName;
public:
    DataBase();
    ~DataBase();
    bool createConnection(const QString& databaseType, const QString& dbName, const QString& userName, const QString& password);
};

#endif // DATABASE_H
