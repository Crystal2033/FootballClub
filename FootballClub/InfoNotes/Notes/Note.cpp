/***************************************************************************
 *                                                                         *
 *   Copyright (C) 14.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "Note.h"
Note::Note(QWidget *parent)
    :QWidget(parent)
{
    modifyButton = new QPushButton("Modify");
    modifyButton->setIcon(QIcon(":/pictures/Pics/modifyData.png"));
}

//void Note::setNoteViewType(const NOTE_VIEW_TYPE type)
//{
//    noteViewType = type;
//}

//NOTE_VIEW_TYPE Note::getNoteViewTytpe() const
//{
//    return noteViewType;
//}
