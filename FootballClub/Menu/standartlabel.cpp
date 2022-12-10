/***************************************************************************
 *                                                                         *
 *   Copyright (C) 10.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "standartlabel.h"

StandartLabel::StandartLabel(const QString labelName, QWidget* parent)
    :MenuLabel(labelName, parent)
{
    labelColor = QColor("#335180");

    QPalette pal = label->palette();
    pal.setColor(label->backgroundRole(), labelColor);
    label->setPalette(pal);
}


