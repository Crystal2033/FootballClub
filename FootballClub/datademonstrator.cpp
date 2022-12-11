/***************************************************************************
 *                                                                         *
 *   Copyright (C) 11.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "datademonstrator.h"
#include <QPushButton>

DataDemonstrator::DataDemonstrator(QBoxLayout* parentLay, QWidget *parent)
    : QWidget{parent}
{
    layout = new QVBoxLayout;

    scrollArea = new QScrollArea();
    scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    this->setLayout(layout);


    scrollArea->setWidgetResizable(true);

    scrollArea->setStyleSheet(""
                              "background-color: #AB5252;"
                              ""
                              ""
                              "");
    scrollArea->setWidget(this);
    parentLay->setAlignment(Qt::AlignTop);

    parentLay->addWidget(scrollArea);

//    for(int i = 0; i < 100; i++){
//        QPushButton* button = new QPushButton(QString::number(i));
//        button->setStyleSheet("background-color:green;");
//        layout->addWidget(button);
//    }
}
