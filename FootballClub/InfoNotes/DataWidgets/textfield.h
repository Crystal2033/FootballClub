/***************************************************************************
 *                                                                         *
 *   Copyright (C) 12.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include <QWidget>
#include <QBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QCalendar>
#include <QLineEdit>
#include <QPushButton>

class TextField : public QWidget
{
    Q_OBJECT
public:
    explicit TextField(QWidget *parent = nullptr);

signals:

};

#endif // TEXTFIELD_H