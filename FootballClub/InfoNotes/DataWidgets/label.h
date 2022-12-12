/***************************************************************************
 *                                                                         *
 *   Copyright (C) 12.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef LABEL_H
#define LABEL_H

#include "textfield.h"



class Label : public TextField
{
public:
    Label(const QString& text);
private:
    QBoxLayout* lay = nullptr;
    QLabel* label = nullptr;
    void setStyles();
    void setText(const QString& text);

};

#endif // LABEL_H
