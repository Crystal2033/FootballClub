QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DataBase/database.cpp \
    InfoNotes/DataWidgets/calendar.cpp \
    InfoNotes/DataWidgets/label.cpp \
    InfoNotes/DataWidgets/lineedit.cpp \
    InfoNotes/DataWidgets/textfield.cpp \
    InfoNotes/playernote.cpp \
    Menu/Labels/authorizationlabel.cpp \
    Menu/Labels/menulabel.cpp \
    Menu/Labels/standartlabel.cpp \
    Menu/headermenu.cpp \
    Repository/dbrepository.cpp \
    WindowManager/windowmanager.cpp \
    datademonstrator.cpp \
    main.cpp \
    mainwindow.cpp \

HEADERS += \
    DataBase/database.h \
    Enums/Enums.h \
    InfoNotes/DataWidgets/calendar.h \
    InfoNotes/DataWidgets/label.h \
    InfoNotes/DataWidgets/lineedit.h \
    InfoNotes/DataWidgets/textfield.h \
    InfoNotes/Note.h \
    InfoNotes/playernote.h \
    Menu/Labels/authorizationlabel.h \
    Menu/Labels/menulabel.h \
    Menu/Labels/standartlabel.h \
    Menu/headermenu.h \
    PatternObserver/observer.h \
    PatternObserver/subject.h \
    Repository/dbrepository.h \
    WindowManager/windowmanager.h \
    datademonstrator.h \
    mainwindow.h \

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
