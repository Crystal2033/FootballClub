/***************************************************************************
 *                                                                         *
 *   Copyright (C) 12.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "datetimetext.h"
#include <QDateTime>
#include <QDate>

DateTimeText::DateTimeText(const QString & text)
{
    QRegularExpression regularExpr("[1-2][0,9]\\d\\d-[0,1]\\d-[0-3]\\d\\s*(?:[01]\\d|2[0123]):(?:[012345]\\d):(?:[012345]\\d)");
    QValidator *validator = new QRegularExpressionValidator(regularExpr);
    lay = new QHBoxLayout;
    lineEdit = new LineEdit(text, validator);
    calendar = new Calendar;
    callCalendarBtn = new QPushButton;
    QIcon icon(":/pictures/Pics/calendarIcon.png");
    callCalendarBtn->setIcon(icon);
    callCalendarBtn->setFixedSize(35, 35);
    callCalendarBtn->setIconSize(callCalendarBtn->size());
    callCalendarBtn->setStyleSheet("border: none;"
                                   ""
                                   "");


    lay->addWidget(lineEdit);
    lay->addWidget(callCalendarBtn);
    setLayout(lay);
    connect(callCalendarBtn, &QPushButton::clicked, this, &DateTimeText::onCallCalendarBtnClicked);
    connect(calendar, &Calendar::dateSaved, this, &DateTimeText::onSavedDateEmission);
}

QString DateTimeText::getText() const
{
    return lineEdit->getText();
}

void DateTimeText::setText(const QString &newValue)
{
    lineEdit->setText(newValue);
}

void DateTimeText::onCallCalendarBtnClicked()
{
    calendar->setWindowModality(Qt::WindowModal);
    calendar->show();
}

void DateTimeText::onSavedDateEmission()
{
    QDateTime date = QDateTime::fromString(lineEdit->getText(), "yyyy-MM-dd hh:mm:ss");
    QString outputDateTime = calendar->getChosenDate().toString("yyyy-MM-dd") + " " + date.time().toString("hh:mm:ss");
    qInfo() << outputDateTime;
    lineEdit->setText(outputDateTime);
}
