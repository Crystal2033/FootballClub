/***************************************************************************
 *                                                                         *
 *   Copyright (C) 10.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef PLAYERNOTE_H
#define PLAYERNOTE_H

#include <QWidget>
#include "Note.h"

class PlayerNote : public Note
{
public:
    void extend() override;
    PlayerNote(QWidget* parent = nullptr);

signals:

};

#endif // PLAYERNOTE_H
