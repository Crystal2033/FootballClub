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
        sendMatchTournaments(matchNote);
    }
    else if(requestStatus == MATCH_STAGES){
        MatchNote* matchNote = (MatchNote*) note;
        sendMatchStages(matchNote);
    }
    else if(requestStatus == MATCH_TEAM_TYPES){
        MatchNote* matchNote = (MatchNote*) note;
        sendMatchTeamTypes(matchNote);
    }
    else if(requestStatus == MATCH_CLUBS){
        MatchNote* matchNote = (MatchNote*) note;
        sendMatchTeamTypes(matchNote);
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

void WindowManager::sendMatchTournaments(MatchNote* const& note)
{
    QSqlQuery* query = repository->getMatchTournamentsQuery();
    if(query != nullptr){
        note->setTournamentComboList(*query);
        delete query;
    }
}

void WindowManager::sendMatchStages(MatchNote * const &note)
{
    QSqlQuery* query = repository->getMatchStagesQuery();
    if(query != nullptr){
        note->setStagesComboList(*query);
        delete query;
    }
}

void WindowManager::sendMatchTeamTypes(MatchNote * const &note)
{
    QSqlQuery* query = repository->getMatchTeamTypesQuery();
    if(query != nullptr){
        note->setTeamTypesComboList(*query);
        delete query;
    }
}

void WindowManager::sendMatchClubs(MatchNote * const &note)
{
    QSqlQuery* query = repository->getMatchTeamTypesQuery();
    if(query != nullptr){
        note->setTeamTypesComboList(*query);
        delete query;
    }
}
