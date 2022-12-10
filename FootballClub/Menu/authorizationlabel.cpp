/***************************************************************************
 *                                                                         *
 *   Copyright (C) 10.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "authorizationlabel.h"

AuthorizationLabel::AuthorizationLabel(const QString labelName, QWidget* parent):
    MenuLabel(labelName, parent)
{
    labelColor = QColor("#52637E");

    QPalette pal = label->palette();
    pal.setColor(label->backgroundRole(), labelColor);
    label->setPalette(pal);
}

