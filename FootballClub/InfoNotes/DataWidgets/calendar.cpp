/***************************************************************************
 *                                                                         *
 *   Copyright (C) 12.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "calendar.h"

Calendar::Calendar()
{
    lay = new QVBoxLayout;
    calendar = new QCalendarWidget();
    saveBtn = new QPushButton("Save date");
    lay->addWidget(calendar);
    lay->addWidget(saveBtn);
    setLayout(lay);
    connect(saveBtn, &QPushButton::clicked, this, &Calendar::onSaveDateClick);
    show();

}

void Calendar::onSaveDateClick()
{
    qInfo() << calendar->selectedDate();
    //calendar->show();
}
