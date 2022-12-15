/***************************************************************************
 *                                                                         *
 *   Copyright (C) 12.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "lineedit.h"

LineEdit::LineEdit(const QString& text, QValidator* validator)
{
    lay = new QHBoxLayout;
    lineEdit = new QLineEdit(text);
    lineEdit->setValidator(validator);
    lineEdit->setAlignment(Qt::AlignCenter);
    lay->addWidget(lineEdit);
    setLayout(lay);
    setStyles();

}

void LineEdit::setText(const QString &text)
{
    lineEdit->setText(text);
}

QString LineEdit::getText() const
{
    return lineEdit->text();
}

void LineEdit::setStyles()
{
    lineEdit->setStyleSheet("color: #212F3C;"
                            "font-size: 20px;"
                            "font-family: Goudy Old Style;"
                            "font-weight: bold;");
}
