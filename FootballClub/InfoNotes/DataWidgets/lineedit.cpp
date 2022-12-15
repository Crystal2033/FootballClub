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
    lineEdit->setFixedWidth(text.size() * 15);
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
    qInfo() << "LineEdit::getText()";
    return lineEdit->text();
}

void LineEdit::setStyles()
{
    lineEdit->setStyleSheet("border: 1px solid black;"
                            "border-radius: 10px;"
                            "color: white;"
                            "font-size: 20px;"
                            "font-family: Goudy Old Style;"
                            "font-weight: bold;");
}
