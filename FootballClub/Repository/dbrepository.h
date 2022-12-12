/***************************************************************************
 *                                                                         *
 *   Copyright (C) 11.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef DBREPOSITORY_H
#define DBREPOSITORY_H
#include "DataBase/database.h"

class DBRepository
{//class for database requests
public:
    DBRepository();
    ~DBRepository();

private:
    QString getMatchReadOnlyRequest() const;
    void testPrint();
    DataBase* database = nullptr;
    bool createConnection();
    friend class WindowManager;
};

#endif // DBREPOSITORY_H
