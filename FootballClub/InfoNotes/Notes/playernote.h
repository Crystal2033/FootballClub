/***************************************************************************
 *                                                                         *
 *   Copyright (C) 10.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef PLAYERNOTE_H
#define PLAYERNOTE_H
#pragma once
#include <QWidget>
#include "BaseNote.h"

class PlayerNote : public BaseNote
{
public:
    void extend() override;
    PlayerNote(QWidget* parent = nullptr);
private:

signals:

};

#endif // PLAYERNOTE_H
