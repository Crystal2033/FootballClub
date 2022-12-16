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
        LABEL_TYPE chosenDataType = this->window->headerMenu->getChosenDataType();
        switch (chosenDataType) {
        case PLAYERS:
            this->window->dataDemonstrator->setVisibleScrollArea(true);
            break;
        case COACHES:
            this->window->dataDemonstrator->setVisibleScrollArea(true);
            break;
        case MATCHES:
            this->window->dataDemonstrator->setVisibleScrollArea(true);
            createAndShowData(chosenDataType, EXIST);
            break;
        case GOALS:
            this->window->dataDemonstrator->setVisibleScrollArea(true);
            break;
        case CLUB:
            this->window->dataDemonstrator->setVisibleScrollArea(false);
            break;
        case TEAMS:
            this->window->dataDemonstrator->setVisibleScrollArea(true);
            break;
        case AUTHO:
            this->window->dataDemonstrator->setVisibleScrollArea(false);
            break;

        default:
            break;
        }
    }
    else if(requestStatus == ADD_NEW_NOTE){
        LABEL_TYPE chosenDataType = this->window->headerMenu->getChosenDataType();

        switch (chosenDataType) {
        case PLAYERS:
            break;
        case COACHES:
            qInfo() << "Add coach";
            break;
        case MATCHES:
            createAndShowData(chosenDataType, NOT_EXIST);
            break;
        case GOALS:
            break;
        case CLUB:
            break;
        case TEAMS:
            break;
        case AUTHO:

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
        MatchNote* matchNote = (MatchNote*) note;
        repository->saveMatchData(matchNote->getFieldsMap());
    }

}






void WindowManager::createAndShowData(const LABEL_TYPE &dataType, const EXISTANCE_STATUS& existStatus)
{
    QSqlQuery* query = getNeededQuery(dataType, existStatus);
    QList<BaseNote*> listOfNotesInfo;
    if(query != nullptr){
        while(query->next()){
            BaseNote* note = createNoteBasedOnType(dataType, query);
            note->addObserver(this);
            listOfNotesInfo.push_back(note);
        }
        delete query;
    }
    else{
        BaseNote* note = createNoteBasedOnType(dataType, query);
        note->addObserver(this);
        listOfNotesInfo.push_back(note);
        listOfNotesInfo.append(this->window->dataDemonstrator->getListOfNotes());
    }
    qInfo() << listOfNotesInfo.size();
    this->window->dataDemonstrator->showData(listOfNotesInfo, dataType);
}

QSqlQuery *WindowManager::getNeededQuery(const LABEL_TYPE &dataType, const EXISTANCE_STATUS& existStatus)
{
    if(existStatus == NOT_EXIST){
        return nullptr;
    }
    else{
        switch (dataType) {
        case PLAYERS:
            break;
        case COACHES:
            break;
        case MATCHES:
            return repository->getMatchesQuery();
            break;
        case GOALS:
            break;
        case CLUB:
            break;
        case TEAMS:
            break;
        case AUTHO:

            break;

        default:
            break;
        }
    }

}

BaseNote *WindowManager::createNoteBasedOnType(const LABEL_TYPE &dataType, QSqlQuery* const& query)
{
    switch (dataType) {
    case PLAYERS:
        break;
    case COACHES:
        break;
    case MATCHES:
        return new MatchNote(query);
        break;
    case GOALS:
        break;
    case CLUB:
        break;
    case TEAMS:
        break;
    case AUTHO:

        break;

    default:
        break;
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
        note->setClubsComboListAndScore(*query);
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

