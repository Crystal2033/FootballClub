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
    MatchNote(QSqlQuery* query = nullptr, QWidget* parent = nullptr);


    ~MatchNote();

private:
    QBoxLayout* tournLay;
    QBoxLayout* stageLay;
    QBoxLayout* teamsTypeLay;
    QBoxLayout* clubsAndScoreLay;
    QBoxLayout* stadiumLay;
    QBoxLayout* dateLay;
    QBoxLayout* buttonsLay;
    QBoxLayout* deleteNoteButtonLay;

    TextField* club1 = nullptr; //PSG
    TextField* teamType1 = nullptr; //MAIN OR YOUNG OR WOMEN
    TextField* club2 = nullptr;
    TextField* teamType2 = nullptr;
    TextField* finalScore = nullptr;
    TextField* stadium = nullptr;
    TextField* gameDate = nullptr;
    TextField* tournament = nullptr;
    TextField* stage = nullptr;

    void setStyles();
    void insertFieldsInMap();
    bool isInsertingDataCorrect() const;
    void saveDataBeforeAction() override;
    void setSavedDataBack();
    void transformNoteInLabelView();
    void setAllDataOnLayout() override;

    void createModifyView();

    void setTournamentComboList(QSqlQuery& query) override;
    void setStagesComboList(QSqlQuery& query) override;
    void setTeamTypesComboList(QSqlQuery& query) override;
    void setClubsComboList(QSqlQuery& query) override;
    void setStadiumsComboList(QSqlQuery& query) override;
    void setNoteViewType(const NOTE_VIEW_TYPE type) override;

private slots:
    void extend() override;
    void modifyNoteView() override;
    void onSaveChangesClicked();
    void onCancelModifyingClicked();
    void onDeleteButtonClicked();
};

#endif // MATCHNOTE_H
