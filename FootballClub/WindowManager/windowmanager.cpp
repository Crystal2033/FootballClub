/***************************************************************************
 *                                                                         *
 *   Copyright (C) 11.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "windowmanager.h"
#include "InfoNotes/Notes/matchnote.h"

WindowManager::WindowManager()
{
    window = new MainWindow(this);
    window->setStyleSheet("MainWindow{background-color: #30415B;}");
    repository = new DBRepository;
}

WindowManager::~WindowManager()
{
    delete repository;
}

void WindowManager::show()
{
    window->show();
}


void WindowManager::updateByObserver(const REQUEST_TYPE requestStatus, BaseNote* note)
{
    if(requestStatus == SEND_CHOSEN_DATA_TYPE){
        switch (this->window->headerMenu->getChosenDataType()) {
        case PLAYERS:
            this->window->dataDemonstrator->setVisibleScrollArea(true);
            qInfo() << "PLAYERS";
            break;
        case COACHES:
            this->window->dataDemonstrator->setVisibleScrollArea(true);
            qInfo() << "COACHES";
            break;
        case MATCHES:
            this->window->dataDemonstrator->setVisibleScrollArea(true);
            qInfo() << "MATCHES";
            createMatchesData();
            break;
        case GOALS:
            this->window->dataDemonstrator->setVisibleScrollArea(true);
            qInfo() << "GOALS";
            break;
        case CLUB:
            this->window->dataDemonstrator->setVisibleScrollArea(false);
            qInfo() << "CLUB";
            break;
        case TEAMS:
            this->window->dataDemonstrator->setVisibleScrollArea(true);
            qInfo() << "TEAMS";
            break;
        case AUTHO:
            this->window->dataDemonstrator->setVisibleScrollArea(false);
            qInfo() << "AUTHO";
            break;

        default:
            break;
        }
    }
    else if(requestStatus == MATCH_TOURNS){
        MatchNote* matchNote = (MatchNote*) note;
        sendTournamentNames(matchNote);
    }
    else if(requestStatus == MATCH_STAGES){
        MatchNote* matchNote = (MatchNote*) note;
        sendStageNames(matchNote);
    }
    else if(requestStatus == MATCH_TEAM_TYPES){
        MatchNote* matchNote = (MatchNote*) note;
        sendTeamTypeNames(matchNote);
    }
    else if(requestStatus == MATCH_CLUBS){
        MatchNote* matchNote = (MatchNote*) note;
        sendClubNames(matchNote);
    }
    else if(requestStatus == MATCH_STADIUMS){
        MatchNote* matchNote = (MatchNote*) note;
        sendStadiumNames(matchNote);
    }
    else if(requestStatus == MATCH_UPDATE){
        qInfo() << "Update";
        MatchNote* matchNote = (MatchNote*) note;
        repository->saveMatchData(matchNote->getFieldsMap());
    }

}






void WindowManager::createMatchesData()
{
    QSqlQuery* query = repository->getMatchesQuery();
    if(query != nullptr){
        QList<BaseNote*> listOfMatchesInfo;

        while(query->next()){
            MatchNote* matchNote = new MatchNote(*query);
            matchNote->addObserver(this);
            listOfMatchesInfo.push_back(matchNote);
        }

        this->window->dataDemonstrator->showData(listOfMatchesInfo);
        delete query;
    }

}

void WindowManager::sendTournamentNames(MatchNote* const& note)
{
    QSqlQuery* query = repository->getTournNamesQuery();
    if(query != nullptr){
        note->setTournamentComboList(*query);
        delete query;
    }
}

void WindowManager::sendStageNames(MatchNote * const &note)
{
    QSqlQuery* query = repository->getStageNamesQuery();
    if(query != nullptr){
        note->setStagesComboList(*query);
        delete query;
    }
}

void WindowManager::sendTeamTypeNames(MatchNote * const &note)
{
    QSqlQuery* query = repository->getTeamTypeNamesQuery();
    if(query != nullptr){
        note->setTeamTypesComboList(*query);
        delete query;
    }
}

void WindowManager::sendClubNames(MatchNote * const &note)
{
    QSqlQuery* query = repository->getClubNamesQuery();
    if(query != nullptr){
        note->setClubsComboList(*query);
        delete query;
    }
}

void WindowManager::sendStadiumNames(MatchNote * const &note)
{
    QSqlQuery* query = repository->getStadiumNamesQuery();
    if(query != nullptr){
        note->setStadiumsComboList(*query);
        delete query;
    }
}
