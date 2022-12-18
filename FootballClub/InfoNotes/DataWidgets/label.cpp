/***************************************************************************
 *                                                                         *
 *   Copyright (C) 12.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "label.h"

Label::Label(const QString& text)
{
    lay = new QHBoxLayout;
    label = new QLabel(text);
    if(text == "PSG"){
        label->setText("<font color=\"#0b2753\">P</font><font color=\"white\">S</font><font color=\"#c3192c\">G</font>");
    }
    lay->addWidget(label);
    setLayout(lay);
    setStyles();
}

void Label::setStyles()
{
    label->setStyleSheet(""
                         "font-size: 20px;"
                         "font-family: Goudy Old Style;"
                         "font-weight: bold;");
}

void Label::setText(const QString &text)
{

    label->setText(text);
}

QString Label::getText() const
{
    return label->text();
}
