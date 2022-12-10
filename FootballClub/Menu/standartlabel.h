/***************************************************************************
 *                                                                         *
 *   Copyright (C) 10.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef STANDARTLABEL_H
#define STANDARTLABEL_H

#include "menulabel.h"
#include <QLabel>

class StandartLabel : public MenuLabel
{
public:
    StandartLabel(const QString labelName, QWidget* parent = nullptr);
private slots:
    void onLabelClicked();
private:


};

#endif // STANDARTLABEL_H
