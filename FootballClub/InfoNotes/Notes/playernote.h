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

    QLabel* gameNumberLbl;
    QLabel* playerNameLbl;
    QLabel* posLbl;
    QLabel* birthdayLbl ;
    QLabel* heightLbl;
    QLabel* weightLbl ;
    QLabel* countryLbl;
    QLabel* teamTypeLbl;
    QLabel* inClubSinceLbl;
    QLabel* contractEndsAtLbl;
    QLabel* salaryLbl;

    QBoxLayout* playerInfoLay = nullptr;
    QBoxLayout* playerNumberLay = nullptr;
    QBoxLayout* playerNameLay = nullptr;
    QBoxLayout* playerPosLay = nullptr;


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


    void setAllDataOnLayout();
    QString deleteNotNeedSymbolsInSalaryValue(QString salaryValue) const;

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

    void createModifyView();

    void setPlayerPositionComboList(QSqlQuery& query) override;
    void setTeamTypesComboList(QSqlQuery& query) override;
    void setCountryComboList(QSqlQuery& query) override;

    void setNoteViewType(const NOTE_VIEW_TYPE type) override;
    void setStyles();
    void insertFieldsInMap() override;
    void saveDataBeforeAction() override;
    void transformNoteInLabelView() override;

    bool isInsertingDataCorrect() const;


private slots:
    void modifyNoteView() override;
    void onSaveChangesClicked();
    void onCancelModifyingClicked();
    void onDeleteButtonClicked();

signals:

};

#endif // PLAYERNOTE_H
