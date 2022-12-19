/***************************************************************************
 *                                                                         *
 *   Copyright (C) 10.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef HEADERMENU_H
#define HEADERMENU_H
#pragma once
#include "Labels/menulabel.h"
#include <QWidget>
#include <QList>
#include <QBoxLayout>
#include <PatternObserver/observer.h>

class HeaderMenu : public QWidget, public InterfaceObserver, public InterfaceSubject
{//OBSERVER FOR MENU LABELS, SUBJECT FOR WindowManager. Observer to change label color if chosen and uncolor other.
 //Subject to send chosen label type to WindowManager
    Q_OBJECT
public:
    explicit HeaderMenu(QWidget *parent = nullptr);
    ~HeaderMenu();

    void updateByObserver(const REQUEST_TYPE requestStatus, BaseNote* note = nullptr) override;

    void addObserver(InterfaceObserver* observer) override;
    void removeObserver(InterfaceObserver* observer) override;
    void removeObservers() override;
    LABEL_TYPE getChosenDataType() const;
    void notifyObservers(const REQUEST_TYPE requestStatus, BaseNote* note = nullptr) override;

private:
    QHBoxLayout* horLay = nullptr;
    LABEL_TYPE chosenDataType = CLUB;
    void createMenu();
    void insertLabelsInLayout();
    void addMenuLabel(MenuLabel* const& menuLabel);
    QList<MenuLabel*> menuLabels;


    QList<InterfaceObserver*> observers;

signals:

};

#endif // HEADERMENU_H
