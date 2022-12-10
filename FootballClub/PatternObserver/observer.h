/***************************************************************************
 *                                                                         *
 *   Copyright (C) 21.08.2022 by Kulikov Pavel                                 *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef OBSERVER_H
#define OBSERVER_H
#include <QImage>

class InterfaceObserver
{
public:
    virtual ~InterfaceObserver() = default;
    virtual void updateByObserver() = 0;
};

#endif // OBSERVER_H
