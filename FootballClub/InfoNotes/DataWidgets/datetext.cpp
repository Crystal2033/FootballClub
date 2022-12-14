/***************************************************************************
 *                                                                         *
 *   Copyright (C) 12.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "datetext.h"
#include <QDateTime>
#include <QDate>

DateText::DateText(const QString & text)
{
    lay = new QHBoxLayout;
    lineEdit = new LineEdit(text);
    calendar = new Calendar;
    callCalendarBtn = new QPushButton;
    callCalendarBtn->setIcon(QIcon(":/pictures/Pics/calendarIcon.jpg"));
    callCalendarBtn->setFixedSize(40, 40);

    lay->addWidget(lineEdit);
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
    QDateTime date = QDateTime::fromString(lineEdit->getText(), "yyyy-MM-dd hh:mm:ss");
    QString outputDateTime = calendar->getChosenDate().toString("yyyy-MM-dd") + " " + date.time().toString("hh:mm:ss");
    qInfo() << outputDateTime;
    lineEdit->setText(outputDateTime);
}
