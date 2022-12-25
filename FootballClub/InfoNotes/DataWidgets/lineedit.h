/***************************************************************************
 *                                                                         *
 *   Copyright (C) 12.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef LINEEDIT_H
#define LINEEDIT_H
#pragma once
#include "textfield.h"

class LineEdit : public TextField
{
    Q_OBJECT
public:
    LineEdit(const QString& text, QValidator* validator = nullptr);
    void setText(const QString& text) override;
    QString getText() const override;
    void setNewFixedSize(unsigned w, unsigned h);
private:
    QLineEdit* lineEdit = nullptr;
    QBoxLayout* lay = nullptr;
    void setStyles();

private slots:
    void editFinished();

signals:
    void emitEditingFinished();
};

#endif // LINEEDIT_H
