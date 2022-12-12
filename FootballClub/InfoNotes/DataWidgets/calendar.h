/***************************************************************************
 *                                                                         *
 *   Copyright (C) 12.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef CALENDAR_H
#define CALENDAR_H

#include "textfield.h"
#include <QCalendarWidget>

class Calendar : public TextField
{
public:
    Calendar();
private:
    QCalendarWidget* calendar = nullptr;
    QPushButton* saveBtn = nullptr;
    QBoxLayout* lay = nullptr;
private slots:
    void onSaveDateClick();

};

#endif // CALENDAR_H
