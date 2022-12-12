/***************************************************************************
 *                                                                         *
 *   Copyright (C) 09.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include <InfoNotes/DataWidgets/datetext.h>
#include <QApplication>
#include <WindowManager/windowmanager.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DateText dt;
    dt.show();
//    WindowManager windowManager;
//    windowManager.show();
    return a.exec();
}
