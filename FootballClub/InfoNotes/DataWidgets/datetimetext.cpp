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
    QRegularExpression regularExpr("[1-2][0,9]\\d\\d-[0,1]\\d-[0-3]\\d\\s*[0-2]\\d:[0-5]\\d:[0-5]\\d");
    QValidator *validator = new QRegularExpressionValidator(regularExpr);
    lay = new QHBoxLayout;
    lineEdit = new LineEdit(text, validator);
    calendar = new Calendar;
    callCalendarBtn = new QPushButton;
    callCalendarBtn->setIcon(QIcon(":/pictures/Pics/calendarIcon.jpg"));
    callCalendarBtn->setFixedSize(40, 40);

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
