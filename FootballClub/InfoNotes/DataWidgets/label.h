/***************************************************************************
 *                                                                         *
 *   Copyright (C) 12.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef LABEL_H
#define LABEL_H
#pragma once
#include "textfield.h"



class Label : public TextField
{
public:
    Label(const QString& text);
    void setText(const QString& text);
    QString getText() const override;
private:
    QBoxLayout* lay = nullptr;
    QLabel* label = nullptr;
    void setStyles();


};

#endif // LABEL_H
