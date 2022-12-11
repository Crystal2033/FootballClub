/***************************************************************************
 *                                                                         *
 *   Copyright (C) 11.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef DATADEMONSTRATOR_H
#define DATADEMONSTRATOR_H

#include <QWidget>
#include <QScrollArea>
#include <QBoxLayout>
#include "InfoNotes/Note.h"

class DataDemonstrator : public QWidget
{
    Q_OBJECT
public:
    explicit DataDemonstrator(QBoxLayout* parentLay, QWidget *parent = nullptr);
private:
    QScrollArea* scrollArea = nullptr;
    QBoxLayout* layout = nullptr;
    //QList<Note*> listOfNotes;

signals:

};

#endif // DATADEMONSTRATOR_H
