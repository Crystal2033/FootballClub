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

#include <PatternObserver/subject.h>
typedef enum {CHOSEN, NOT_CHOSEN} CHOSEN_TYPE;
class MenuLabel : public QWidget, public InterfaceSubject
{
    Q_OBJECT
public:
    explicit MenuLabel(const QString labelName, QWidget *parent = nullptr);
    void setChosen(const bool chosenStatus);
    QString getText();
    void addObserver(InterfaceObserver *observer);
    void removeObserver(InterfaceObserver *observer);
    void setBaseColor();
protected:
    QList<InterfaceObserver*> observers;
    bool isChosen = false;
    QVBoxLayout* mainLay = nullptr;
    QLabel* label;
    QColor baseColor;
    QColor labelColor;
    void createStyles();
    void setBackgroundLabelColor();

    void mousePressEvent(QMouseEvent* event);
    void notifyObservers();

private:

signals:
    void clicked();
};

#endif // MENULABEL_H
