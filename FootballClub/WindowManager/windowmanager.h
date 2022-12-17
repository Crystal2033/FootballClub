/***************************************************************************
 *                                                                         *
 *   Copyright (C) 11.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H
#pragma once
#include "mainwindow.h"
#include "Repository/dbrepository.h"
#include "InfoNotes/Notes/matchnote.h"

class WindowManager : public InterfaceObserver
{
public:
    WindowManager();
    ~WindowManager();
    void show();
private:
    MainWindow* window = nullptr;
    DBRepository* repository = nullptr;
    void updateByObserver(const REQUEST_TYPE requestStatus, BaseNote* note = nullptr) override;

    void createAndShowData(const LABEL_TYPE& dataType, const EXISTANCE_STATUS& existStatus);
    QSqlQuery* getNeededQuery(const LABEL_TYPE& dataType, const EXISTANCE_STATUS& existStatus);
    BaseNote* createNoteBasedOnType(const LABEL_TYPE& dataType, QSqlQuery* const& query);

    void sendTournamentNames(BaseNote* const& note);
    void sendStageNames(BaseNote* const& note);
    void sendTeamTypeNames(BaseNote* const& note);
    void sendClubNames(BaseNote* const& note);
    void sendStadiumNames(BaseNote* const& note);
    bool postNote(BaseNote* note, const LABEL_TYPE type);

    bool postMatchNote(MatchNote* note);
public slots:
};

#endif // WINDOWMANAGER_H
