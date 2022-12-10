/***************************************************************************
 *                                                                         *
 *   Copyright (C) 10.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef MENULABEL_H
#define MENULABEL_H

#include <QWidget>
#include <QLabel>
#include <QBoxLayout>
#include "Enums/Enums.h"
#include <PatternObserver/subject.h>

class MenuLabel : public QWidget, public InterfaceSubject
{
    Q_OBJECT
public:
    explicit MenuLabel(const QString labelName, const LABEL_TYPE labelType, QWidget *parent = nullptr);
    virtual void setChosenAndChangeColor(const bool chosenStatus);
    QString getText() const;
    void addObserver(InterfaceObserver *observer);
    void removeObserver(InterfaceObserver *observer);
    bool getIsChosen() const;
    LABEL_TYPE getLabelType() const;
protected:
    QList<InterfaceObserver*> observers;
    bool isChosen = false;
    QVBoxLayout* mainLay = nullptr;
    QLabel* label;
    LABEL_TYPE labelType;
    QColor baseColor;
    QColor labelColor;
    void createStyles();
    void setBackgroundLabelColor();

    void mousePressEvent(QMouseEvent* event);
    void notifyObservers(const REQUEST_TYPE requestStatus);

private:

signals:
    void clicked();
};

#endif // MENULABEL_H
