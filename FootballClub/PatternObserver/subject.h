/***************************************************************************
 *                                                                         *
 *   Copyright (C) 21.08.2022 by Kulikov Pavel                                 *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef SUBJECT_H
#define SUBJECT_H
#pragma once
#include "observer.h"

class InterfaceSubject
{
public:
    virtual ~InterfaceSubject() = default;
    virtual void addObserver(InterfaceObserver* observer) = 0;
    virtual void removeObserver(InterfaceObserver* observer) = 0;
    virtual void notify() = 0;
};


#endif // SUBJECT_H
