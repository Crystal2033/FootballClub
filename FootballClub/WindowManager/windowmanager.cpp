/***************************************************************************
 *                                                                         *
 *   Copyright (C) 11.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "windowmanager.h"



WindowManager::WindowManager()
{
    window = new MainWindow(this);
    window->setStyleSheet("MainWindow{background-color: #30415B}");

    repository = new DBRepository;
    repository->testPrint();
}

WindowManager::~WindowManager()
{
    delete repository;
}

void WindowManager::show()
{
    window->show();
}


void WindowManager::updateByObserver(const REQUEST_TYPE requestStatus)
{
    switch (this->window->headerMenu->getChosenDataType()) {
    case PLAYERS:
        qInfo() << "PLAYERS";
        break;
    case COACHES:
        qInfo() << "COACHES";
        break;
    case MATCHES:
        qInfo() << "MATCHES";
        createMatchesData();
        break;
    case TOURNS:
        qInfo() << "TOURNS";
        break;
    case GOALS:
        qInfo() << "GOALS";
        break;
    case CLUB:
        qInfo() << "CLUB";
        break;
    case TEAMS:
        qInfo() << "TEAMS";
        break;
    case AUTHO:
        qInfo() << "AUTHO";
        break;

    default:
        break;
    }
}

void WindowManager::createMatchesData()
{
    QSqlQuery* query = repository->getMatchesQuery();
    QSqlRecord record = query->record();
    QList<Note*> listOfMatchesInfo;
    while(query->next()){
        listOfMatchesInfo.push_back(new MatchNote(*query, record));
    }

    this->window->dataDemonstrator->showData(listOfMatchesInfo);

}
