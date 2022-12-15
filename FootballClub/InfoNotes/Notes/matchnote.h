/***************************************************************************
 *                                                                         *
 *   Copyright (C) 12.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef MATCHNOTE_H
#define MATCHNOTE_H
#pragma once
#include "BaseNote.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include "InfoNotes/DataWidgets/textfield.h"
#include <map>

class MatchNote : public BaseNote
{
public:
    MatchNote(QSqlQuery& query, QWidget* parent = nullptr);

    void setTournamentComboList(QSqlQuery& query);
    void setStagesComboList(QSqlQuery& query);
    void setTeamTypesComboList(QSqlQuery& query);
    void setClubsComboList(QSqlQuery& query);
    void setStadiumsComboList(QSqlQuery& query);
    std::map<QString, TextField*> getFieldsMap() const;
    ~MatchNote();
private:
    std::map<QString, TextField*> fieldsMap;
    QBoxLayout* tournLay;
    QBoxLayout* stageLay;
    QBoxLayout* teamsTypeLay;
    QBoxLayout* teamsAndScoreLay;
    QBoxLayout* stadiumLay;
    QBoxLayout* dateLay;
    QBoxLayout* buttonsLay;


    TextField* team1 = nullptr; //PSG
    TextField* teamType1 = nullptr; //MAIN OR YOUNG OR WOMEN
    TextField* team2 = nullptr;
    TextField* teamType2 = nullptr;
    TextField* finalScore = nullptr;
    TextField* stadium = nullptr;
    TextField* gameDate = nullptr;
    TextField* tournament = nullptr;
    TextField* stage = nullptr;

    void setStyles();
    void insertFieldsInMap();

private slots:
    void extend() override;
    void modifyNoteView() override;
    void onSaveChangesClicked();
    void onCancelModifyingClicked();
};

#endif // MATCHNOTE_H
