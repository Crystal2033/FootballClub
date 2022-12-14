/***************************************************************************
 *                                                                         *
 *   Copyright (C) 12.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef MATCHNOTE_H
#define MATCHNOTE_H

#include "BaseNote.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include "InfoNotes/DataWidgets/textfield.h"

class MatchNote : public BaseNote
{
public:
    MatchNote(QSqlQuery& query, QSqlRecord & record, QWidget* parent = nullptr);
    ~MatchNote() = default;
private:
    void extend() override;
    void modifyNoteView() override;
    QBoxLayout* leftWidgetsLay = nullptr;
    QBoxLayout* middleWidgetsLay = nullptr;
    QBoxLayout* rightWidgetsLay = nullptr;

    TextField* team1 = nullptr; //PSG
    TextField* teamType1 = nullptr; //MAIN OR YOUNG OR WOMEN
    TextField* team2 = nullptr;
    TextField* teamType2 = nullptr;
    TextField* finalScore = nullptr;
    TextField* stadium = nullptr;
    TextField* gameDate = nullptr;
    TextField* tournament = nullptr;
    TextField* stage = nullptr;
};

#endif // MATCHNOTE_H
