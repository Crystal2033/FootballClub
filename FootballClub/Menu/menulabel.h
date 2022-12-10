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
typedef enum {CHOSEN, NOT_CHOSEN} CHOSEN_TYPE;
class MenuLabel : public QWidget
{
    Q_OBJECT
public:
    explicit MenuLabel(const QString labelName, QWidget *parent = nullptr);
    void setChosen(const bool chosenStatus);
protected:
    bool isChosen = false;
    QLabel* label;
    QColor labelColor;
    virtual void createStyles();
signals:

};

#endif // MENULABEL_H
