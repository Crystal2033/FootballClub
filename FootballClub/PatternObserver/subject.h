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
#include "PatternObserver/observer.h"

class InterfaceSubject
{
public:
    virtual ~InterfaceSubject() = default;
    virtual void addObserver(InterfaceObserver* observer) = 0;
    virtual void removeObserver(InterfaceObserver* observer) = 0;
    virtual void removeObservers() = 0;
    virtual void notifyObservers(const REQUEST_TYPE requestStatus, BaseNote* note = nullptr) = 0;
};


#endif // SUBJECT_H
