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
    LineEdit();
private:
    QLineEdit* lineEdit = nullptr;
    QBoxLayout* lay = nullptr;

    void setText(const QString& text);
    QString getText() const;
    void setStyles();

};

#endif // LINEEDIT_H
