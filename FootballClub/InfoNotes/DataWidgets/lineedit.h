/***************************************************************************
 *                                                                         *
 *   Copyright (C) 12.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef LINEEDIT_H
#define LINEEDIT_H

#include "textfield.h"

class LineEdit : public TextField
{
public:
    LineEdit(const QString& text);
    void setText(const QString& text);
    QString getText() const;
private:
    QLineEdit* lineEdit = nullptr;
    QBoxLayout* lay = nullptr;


    void setStyles();

};

#endif // LINEEDIT_H
