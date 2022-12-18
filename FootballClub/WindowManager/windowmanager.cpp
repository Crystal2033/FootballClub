/***************************************************************************
 *                                                                         *
 *   Copyright (C) 11.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "windowmanager.h"
#include "InfoNotes/Notes/managernote.h"
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
            createAndShowData(chosenDataType, EXIST);
            break;
        case COACHES:
            this->window->dataDemonstrator->setVisibleScrollArea(true);
            createAndShowData(chosenDataType, EXIST);
            break;
        case MATCHES:
            this->window->dataDemonstrator->setVisibleScrollArea(true);
            createAndShowData(chosenDataType, EXIST);
            break;
        case CLUB:
            this->window->dataDemonstrator->setVisibleScrollArea(false);
            showClubData(chosenDataType);
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
            createAndShowData(chosenDataType, NOT_EXIST);
            break;
        case COACHES:
            createAndShowData(chosenDataType, NOT_EXIST);
            break;
        case MATCHES:
            createAndShowData(chosenDataType, NOT_EXIST);
            break;
        default:
            break;
        }
    }
    else if(requestStatus == GET_TOURNS){
        sendTournamentNames(note);
    }
    else if(requestStatus == GET_STAGES){
        sendStageNames(note);
    }
    else if(requestStatus == GET_TEAM_TYPES){
        sendTeamTypeNames(note);
    }
    else if(requestStatus == GET_CLUBS){
        sendClubNames(note);
    }
    else if(requestStatus == GET_STADIUMS){
        sendStadiumNames(note);
    }
    else if(requestStatus == GET_PLAYER_POSES){
        sendPlayerPositionNames(note);
    }
    else if(requestStatus == GET_COUNTRIES){
        sendCountryNames(note);
    }
    else if(requestStatus == GET_MANAGER_TITLES){
        sendManagerTitleNames(note);
    }
    else if(requestStatus == UPDATE){
        repository->saveData(this->window->headerMenu->getChosenDataType(), note->getFieldsMap(), note->getRecordId());
    }
    else if(requestStatus == DELETE){
        if(repository->deleteData(this->window->headerMenu->getChosenDataType(), note->getRecordId())){
            this->window->dataDemonstrator->deleteNoteFromList(note);
            delete note;
            this->window->dataDemonstrator->showData(this->window->dataDemonstrator->getListOfNotes());
        }
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
        note->setNoteViewType(WRITE);
        if(postNote(note, dataType)){
            listOfNotesInfo.push_back(note);
        }
        listOfNotesInfo.append(this->window->dataDemonstrator->getListOfNotes());
    }
    this->window->dataDemonstrator->showData(listOfNotesInfo);
}

QSqlQuery *WindowManager::getNeededQuery(const LABEL_TYPE &dataType, const EXISTANCE_STATUS& existStatus)
{
    if(existStatus == NOT_EXIST){
        return nullptr;
    }
    else{
        switch (dataType) {
        case PLAYERS:
            return repository->getPlayersQuery();
        case COACHES:
            return repository->getManagersQuery();
        case MATCHES:
            return repository->getMatchesQuery();
        case CLUB:
            return repository->getClubQuery();

        default:
            break;
        }
    }
    return nullptr;
}

BaseNote *WindowManager::createNoteBasedOnType(const LABEL_TYPE &dataType, QSqlQuery* const& query)
{
    switch (dataType) {
        case PLAYERS:
            return new PlayerNote(query);
        case COACHES:
            return new ManagerNote(query);
        case MATCHES:
            return new MatchNote(query);

        default:
            break;
    }
    return nullptr;
}


void WindowManager::sendTournamentNames(BaseNote* const& note)
{
    QSqlQuery* query = repository->getTournNamesQuery();
    if(query != nullptr){
        note->setTournamentComboList(*query);
        delete query;
    }
}

void WindowManager::sendStageNames(BaseNote * const &note)
{
    QSqlQuery* query = repository->getStageNamesQuery();
    if(query != nullptr){
        note->setStagesComboList(*query);
        delete query;
    }
}

void WindowManager::sendTeamTypeNames(BaseNote * const &note)
{
    QSqlQuery* query = repository->getTeamTypeNamesQuery();
    if(query != nullptr){
        note->setTeamTypesComboList(*query);
        delete query;
    }
}

void WindowManager::sendClubNames(BaseNote * const &note)
{
    QSqlQuery* query = repository->getClubNamesQuery();
    if(query != nullptr){
        note->setClubsComboList(*query);
        delete query;
    }
}

void WindowManager::sendStadiumNames(BaseNote * const &note)
{
    QSqlQuery* query = repository->getStadiumNamesQuery();
    if(query != nullptr){
        note->setStadiumsComboList(*query);
        delete query;
    }
}

void WindowManager::sendCountryNames(BaseNote * const &note)
{
    QSqlQuery* query = repository->getCountryNamesQuery();
    if(query != nullptr){
        note->setCountryComboList(*query);
        delete query;
    }
}

void WindowManager::sendPlayerPositionNames(BaseNote * const &note)
{
    QSqlQuery* query = repository->getPlayerPositionNamesQuery();
    if(query != nullptr){
        note->setPlayerPositionComboList(*query);
        delete query;
    }
}

void WindowManager::sendManagerTitleNames(BaseNote * const &note)
{
    QSqlQuery* query = repository->getManagerTitlesQuery();
    if(query != nullptr){
        note->setManagerTitleComboList(*query);
        delete query;
    }
}



bool WindowManager::postNote(BaseNote *note, const LABEL_TYPE type)
{
    int newNoteId;
    switch (type) {
    case PLAYERS:
        newNoteId = repository->postData(type, note->getFieldsMap());
        break;
    case COACHES:
        newNoteId = repository->postData(type, note->getFieldsMap());
        break;
    case MATCHES:
        newNoteId = repository->postData(type, note->getFieldsMap());
        break;

    default:
        return false;
    }
    if(newNoteId == -1){
        return false;
    }
    note->setRecordId(newNoteId);
    return true;
}

void WindowManager::showClubData(const LABEL_TYPE &dataType)
{
    QSqlQuery* query = getNeededQuery(dataType, EXIST);
    QSqlRecord record = query->record();
    query->next();
    QString clubCreatedAt = query->value(record.indexOf("created_at")).toString();
    this->window->dataDemonstrator->showClubData(clubCreatedAt);
    delete query;
}



