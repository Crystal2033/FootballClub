/***************************************************************************
 *                                                                         *
 *   Copyright (C) 12.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef DATETEXT_H
#define DATETEXT_H

#include "textfield.h"
#include "calendar.h"
#include "label.h"

class DateText : public TextField
{
public:
    DateText();
private:
    QBoxLayout* lay = nullptr;
    Label* label = nullptr;
    QPushButton* callCalendarBtn = nullptr;
    Calendar* calendar = nullptr;
private slots:
    void onCallCalendarBtnClicked();
    void onSavedDateEmission();
};

#endif // DATETEXT_H
