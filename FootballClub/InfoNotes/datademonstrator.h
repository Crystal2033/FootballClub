/***************************************************************************
 *                                                                         *
 *   Copyright (C) 11.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef DATADEMONSTRATOR_H
#define DATADEMONSTRATOR_H
#include "InfoNotes/DataWidgets/lineedit.h"
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
    bool isAdmin = false;
    explicit DataDemonstrator(QBoxLayout* parentLay, QWidget *parent = nullptr);
    void showData(const QList<BaseNote*>& notes, const LABEL_TYPE& currDataType);
    void setVisibleScrollArea(const bool visibility);
    QList<BaseNote*> getListOfNotes() const;

    void deleteDataFromListIfNotNeed(const QList<BaseNote*>& newNotes);
    void addObserver(InterfaceObserver* observer) override;
    void removeObserver(InterfaceObserver* observer) override;
    void removeObservers() override;
    void deleteNoteFromList(const BaseNote* note);
    void showClubData(const QString& createdDate);

    QString getSearchText() const;
    void clearSearchText();

    LABEL_TYPE getCurrShowingData() const;
    LABEL_TYPE currShowingDataType;

private:
    QBoxLayout* searchLay = nullptr;
    QLabel* seacrhLabel = nullptr;
    //QIcon searchIcon;
    LineEdit* searchLineEdit = nullptr;

    QBoxLayout* parentLay;
    QList<InterfaceObserver*> observers;
    QPushButton* addNoteButton = nullptr;
    QScrollArea* scrollArea = nullptr;
    QBoxLayout* layout = nullptr;
    QList<BaseNote*> listOfNotes;
    QBoxLayout* clubAndDevInfoLay = nullptr;
    QLabel* iconLabel = nullptr;
    QIcon logoIcon;
    QLabel* dataOfClubCreation = nullptr;
    QLabel* developerInfo = nullptr;
    void deleteClubAndDevInfo();
    void notifyObservers(const REQUEST_TYPE requestStatus, BaseNote* note = nullptr) override;

private slots:
    void onAddNoteButtonClicked();
    void searchEditingFinished();

};

#endif // DATADEMONSTRATOR_H
