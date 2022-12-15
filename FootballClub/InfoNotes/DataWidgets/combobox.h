/***************************************************************************
 *                                                                         *
 *   Copyright (C) 12.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef COMBOBOX_H
#define COMBOBOX_H
#pragma once
#include "textfield.h"

class ComboBox : public TextField
{
    Q_OBJECT
public:
    ComboBox(const QStringList& stringList);
    QString getChosenData() const;
    void setBoxItems(const QStringList& stringList);
    void setCurrentItem(const QString& text);
private:
    QBoxLayout* lay = nullptr;
    QComboBox* comboBox = nullptr;
    void setStyles();
};

#endif // COMBOBOX_H
