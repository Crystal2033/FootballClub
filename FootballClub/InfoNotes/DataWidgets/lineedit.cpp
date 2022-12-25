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
    lineEdit->setFixedWidth((text.size() <= 3 ) ? 100 : text.size() * 20);
    lay->addWidget(lineEdit);
    setLayout(lay);
    setStyles();
    connect(lineEdit, &QLineEdit::editingFinished, this, &LineEdit::editFinished);

}

void LineEdit::setText(const QString &text)
{
    lineEdit->setText(text);

}

QString LineEdit::getText() const
{
    return lineEdit->text();

}

void LineEdit::setNewFixedSize(unsigned w, unsigned h)
{
    lineEdit->setFixedSize(w, h);
}

void LineEdit::setStyles()
{
    lineEdit->setStyleSheet("border: 1px solid #4d66a4;"
                            "border-radius: 5px;"
                            "color: white;"
                            "font-size: 25px;"
                            "font-family: Goudy Old Style;"
                            "font-weight: bold;");
}

void LineEdit::editFinished()
{
    emit emitEditingFinished();
}
