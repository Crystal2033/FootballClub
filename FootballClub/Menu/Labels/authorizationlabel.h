/***************************************************************************
 *                                                                         *
 *   Copyright (C) 10.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef AUTHORIZATIONLABEL_H
#define AUTHORIZATIONLABEL_H
#pragma once
#include "menulabel.h"

class AuthorizationLabel : public MenuLabel
{
public:
    AuthorizationLabel(const QString labelName, const LABEL_TYPE labelType, QWidget* parent = nullptr);
    void setChosenAndChangeColor(const bool status);
private slots:
    void onLabelClicked();
private:

};

#endif // AUTHORIZATIONLABEL_H
