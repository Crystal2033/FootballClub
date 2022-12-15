/***************************************************************************
 *                                                                         *
 *   Copyright (C) 12.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "combobox.h"

ComboBox::ComboBox(const QStringList& stringList)
{
    lay = new QHBoxLayout;
    comboBox = new QComboBox();
    lay->addWidget(comboBox);
    setLayout(lay);
    setStyles();
    setBoxItems(stringList);
    this->stringList = stringList;
}

QString ComboBox::getChosenData() const
{
    return comboBox->currentText();
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

void ComboBox::setStyles()
{
    comboBox->setStyleSheet("color: white;"
                            "font-size: 20px;"
                            "font-family: Goudy Old Style;"
                            "font-weight: bold;");
}
