/***************************************************************************
 *                                                                         *
 *   Copyright (C) 12.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "lineedit.h"

LineEdit::LineEdit()
{
    lay = new QHBoxLayout;
    lineEdit = new QLineEdit("Unknown");
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
    //TODO:
}
