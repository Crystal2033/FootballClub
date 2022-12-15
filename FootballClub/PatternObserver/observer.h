/***************************************************************************
 *                                                                         *
 *   Copyright (C) 21.08.2022 by Kulikov Pavel                                 *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef OBSERVER_H
#define OBSERVER_H

#pragma once
#include "Enums/Enums.h"

class BaseNote;
class InterfaceObserver
{
public:
    virtual ~InterfaceObserver() = default;
    virtual void updateByObserver(const REQUEST_TYPE requestStatus, BaseNote* note =nullptr) = 0;
};

#endif // OBSERVER_H
