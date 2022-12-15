/***************************************************************************
 *                                                                         *
 *   Copyright (C) 12.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef DATETEXT_H
#define DATETEXT_H
#pragma once
#include "textfield.h"
#include "calendar.h"
#include "lineedit.h"

class DateText : public TextField
{
public:
    DateText(const QString & text);
private:
    QBoxLayout* lay = nullptr;
    LineEdit* lineEdit = nullptr;
    QPushButton* callCalendarBtn = nullptr;
    Calendar* calendar = nullptr;
private slots:
    void onCallCalendarBtnClicked();
    void onSavedDateEmission();
};

#endif // DATETEXT_H
