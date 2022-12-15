/***************************************************************************
 *                                                                         *
 *   Copyright (C) 12.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef DATETIMETEXT_H
#define DATETIMETEXT_H
#pragma once
#include "textfield.h"
#include "calendar.h"
#include "lineedit.h"

class DateTimeText : public TextField
{
public:
    DateTimeText(const QString & text);
private:
    QBoxLayout* lay = nullptr;
    LineEdit* lineEdit = nullptr;
    QPushButton* callCalendarBtn = nullptr;
    Calendar* calendar = nullptr;
    QString getText() const override;
private slots:
    void onCallCalendarBtnClicked();
    void onSavedDateEmission();
};

#endif // DATETEXT_H
