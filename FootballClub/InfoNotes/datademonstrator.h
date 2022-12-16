/***************************************************************************
 *                                                                         *
 *   Copyright (C) 11.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef DATADEMONSTRATOR_H
#define DATADEMONSTRATOR_H
#pragma once
#include "Enums/Enums.h"
#include <QWidget>
#include <QScrollArea>
#include <QBoxLayout>
#include <QtSql>
#include <QPushButton>
class BaseNote;

class DataDemonstrator : public QWidget
{
    Q_OBJECT
public:
    explicit DataDemonstrator(QBoxLayout* parentLay, QWidget *parent = nullptr);
    void showData(const QList<BaseNote*>& notes, const LABEL_TYPE dataType);
    void setVisibleScrollArea(const bool visibility);
    QList<BaseNote*> getListOfNotes() const;
    void deleteDataFromList();
private:
    QPushButton* addNoteButton = nullptr;
    QScrollArea* scrollArea = nullptr;
    QBoxLayout* layout = nullptr;
    QList<BaseNote*> listOfNotes;
    void connectAddButtonToSlot(const LABEL_TYPE dataType);

signals:

};

#endif // DATADEMONSTRATOR_H
