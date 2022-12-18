/***************************************************************************
 *                                                                         *
 *   Copyright (C) 12.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "combobox.h"

ComboBox::ComboBox(const std::map<QString, unsigned>& valueAndIdMap)
{
    this->valueAndIdMap = valueAndIdMap;
    lay = new QHBoxLayout;
    comboBox = new QComboBox();
    lay->addWidget(comboBox);
    setLayout(lay);
    setStyles();
    QStringList stringList = fromMapToStringList();
    setBoxItems(stringList);
    this->stringList = stringList;
}

void ComboBox::setBoxItems(const QStringList &stringList)
{
    if(stringList.isEmpty()){
        QMessageBox::critical(nullptr, "Bad combo box", "String list is empty");
    }
    comboBox->clear();
    comboBox->addItems(stringList);
}

void ComboBox::setCurrentItem(const QString& text)
{
    comboBox->setCurrentText(text);
}

QStringList ComboBox::getStringList() const
{
    return stringList;
}

QString ComboBox::getText() const
{
    return comboBox->currentText();
}

void ComboBox::setText(const QString &newValue)
{
    setCurrentItem(newValue);
}

int ComboBox::getIdByValue(const QString &value)
{
    if(valueAndIdMap.find(value) == valueAndIdMap.end()){
        return -1;
    }
    else{
        return valueAndIdMap.find(value)->second;
    }

}

std::map<QString, unsigned> ComboBox::getValueAndIdMap() const
{
    return valueAndIdMap;
}

QStringList ComboBox::fromMapToStringList() const
{
    QStringList stringList;
    for(auto val : valueAndIdMap){
        qInfo() << "id = " << val.second;
        stringList << val.first;
    }
    return stringList;
}

void ComboBox::setStyles()
{
    comboBox->setStyleSheet("color: white;"
                            "font-size: 20px;"
                            "font-family: Goudy Old Style;"
                            "font-weight: bold;");
}
