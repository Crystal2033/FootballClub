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
            createAndShowData(chosenDataType, EXIST);
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
    else if(requestStatus == UPDATE){
        repository->saveData(this->window->headerMenu->getChosenDataType(), note->getFieldsMap(), note->getRecordId());
    }
    else if(requestStatus == DELETE){
        if(repository->deleteMatchData(note->getRecordId())){
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
        return new PlayerNote(query);
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



bool WindowManager::postNote(BaseNote *note, const LABEL_TYPE type)
{
    int newNoteId;


    switch (type) {
    case PLAYERS:
        break;
    case COACHES:
        break;
    case MATCHES:
        newNoteId = repository->postMatchData(note->getFieldsMap());
        break;
    case GOALS:
        break;
    case CLUB:
        break;
    case TEAMS:
        break;

    default:
        break;
    }
    if(newNoteId == -1){
        return false;
    }
    note->setRecordId(newNoteId);
    return true;
}

bool WindowManager::postMatchNote(MatchNote *note)
{//делается не через observer, так как мы добавляем observer в note после создания. А нам надо как-то дернуть notify
    int newNoteId = repository->postMatchData(note->getFieldsMap());
    if(newNoteId == -1){
        return false;
    }
    note->setRecordId(newNoteId);
    return true;
}

