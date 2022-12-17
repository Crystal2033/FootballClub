/***************************************************************************
 *                                                                         *
 *   Copyright (C) 10.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef PLAYERNOTE_H
#define PLAYERNOTE_H
#pragma once
#include <QWidget>
#include "BaseNote.h"

class PlayerNote : public BaseNote
{
public:
    void extend() override;
    PlayerNote(QSqlQuery* query = nullptr, QWidget* parent = nullptr);
private:
    QBoxLayout* playerInfoLay = nullptr;
    QBoxLayout* playerNumberLay = nullptr;
    QBoxLayout* playerNameLay = nullptr;


    QBoxLayout* personInfoLay = nullptr;
    QBoxLayout* personBirthdayLay = nullptr;
    QBoxLayout* personHeightLay = nullptr;
    QBoxLayout* personWeightLay = nullptr;
    QBoxLayout* personCountryLay = nullptr;

    QBoxLayout* clubInfoLay = nullptr;
    QBoxLayout* clubInfoTeamTypeLay = nullptr;
    QBoxLayout* clubInfoSinceLay = nullptr;
    QBoxLayout* clubInfoLeftAtLay = nullptr;

    QBoxLayout* salaryLay = nullptr;
    void setAllDataOnLayout() override;

    TextField* gameNumber = nullptr;
    TextField* name = nullptr;
    TextField* position = nullptr;
    TextField* birthdayDate = nullptr;
    TextField* height = nullptr;
    TextField* weight = nullptr;
    TextField* countryFrom = nullptr;
    TextField* teamType = nullptr;
    TextField* sinceInClub = nullptr;
    TextField* contractEndsAt = nullptr;
    TextField* salary = nullptr;


    void setTournamentComboList(QSqlQuery& query) override;
    void setStagesComboList(QSqlQuery& query) override;
    void setTeamTypesComboList(QSqlQuery& query) override;
    void setClubsComboList(QSqlQuery& query) override;
    void setStadiumsComboList(QSqlQuery& query) override;
    void setNoteViewType(const NOTE_VIEW_TYPE type) override;

signals:

};

#endif // PLAYERNOTE_H
