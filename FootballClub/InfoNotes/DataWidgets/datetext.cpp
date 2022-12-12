/***************************************************************************
 *                                                                         *
 *   Copyright (C) 12.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "datetext.h"

DateText::DateText()
{
    lay = new QHBoxLayout;
    label = new Label("Unknown");
    calendar = new Calendar;
    callCalendarBtn = new QPushButton;
    callCalendarBtn->setIcon(QIcon(":/pictures/Pics/calendarIcon.jpg"));
    callCalendarBtn->setFixedSize(40, 40);

    lay->addWidget(label);
    lay->addWidget(callCalendarBtn);
    setLayout(lay);
    connect(callCalendarBtn, &QPushButton::clicked, this, &DateText::onCallCalendarBtnClicked);
    connect(calendar, &Calendar::dateSaved, this, &DateText::onSavedDateEmission);
}

void DateText::onCallCalendarBtnClicked()
{
    calendar->setWindowModality(Qt::WindowModal);
    calendar->show();
}

void DateText::onSavedDateEmission()
{
    label->setText(calendar->getChosenDate().toString(Qt::DateFormat::TextDate));
}
