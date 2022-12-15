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

class MatchNote : public BaseNote
{
public:
    MatchNote(QSqlQuery& query, QSqlRecord & record, QWidget* parent = nullptr);
    ~MatchNote();
private:
    void extend() override;
    void modifyNoteView() override;

    QBoxLayout* tournLay;
    QBoxLayout* stageLay;
    QBoxLayout* teamsType;
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

    QPushButton* saveChangesButton;

    void setStyles();
};

#endif // MATCHNOTE_H
