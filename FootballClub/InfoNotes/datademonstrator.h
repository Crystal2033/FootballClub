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
#include "InfoNotes/Notes/BaseNote.h"
#include "Enums/Enums.h"
#include <QWidget>
#include <QScrollArea>
#include <QBoxLayout>
#include <QtSql>
#include <QPushButton>
class WindowManager;

class DataDemonstrator : public QWidget, public InterfaceSubject
{
    Q_OBJECT
public:
    explicit DataDemonstrator(QBoxLayout* parentLay, QWidget *parent = nullptr);
    void showData(const QList<BaseNote*>& notes, const LABEL_TYPE dataType);
    void setVisibleScrollArea(const bool visibility);
    QList<BaseNote*> getListOfNotes() const;
    void deleteDataFromListIfNotNeed(const QList<BaseNote*>& newNotes);
    void addObserver(InterfaceObserver* observer) override;
    void removeObserver(InterfaceObserver* observer) override;
    void removeObservers() override;

private:
    QList<InterfaceObserver*> observers;
    QPushButton* addNoteButton = nullptr;
    QScrollArea* scrollArea = nullptr;
    QBoxLayout* layout = nullptr;
    QList<BaseNote*> listOfNotes;
    void notifyObservers(const REQUEST_TYPE requestStatus, BaseNote* note = nullptr) override;

private slots:
    void onAddNoteButtonClicked();

};

#endif // DATADEMONSTRATOR_H
