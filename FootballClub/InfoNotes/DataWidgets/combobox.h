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
#include <map>

class ComboBox : public TextField
{
    Q_OBJECT
public:
    ComboBox(const std::map<QString, unsigned>& valueAndIdMap);
    QStringList stringList;
    void setBoxItems(const QStringList& stringList);
    void setCurrentItem(const QString& text);
    QStringList getStringList() const;
    QString getText() const override;
    void setText(const QString& newValue) override;
    int getIdByValue(const QString& value);
    std::map<QString, unsigned> getValueAndIdMap() const;
private:
    std::map<QString, unsigned> valueAndIdMap;
    QStringList fromMapToStringList() const;
    QBoxLayout* lay = nullptr;
    QComboBox* comboBox = nullptr;
    void setStyles();
};

#endif // COMBOBOX_H
