/***************************************************************************
 *                                                                         *
 *   Copyright (C) 09.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma once
#include "Menu/headermenu.h"
#include <QMainWindow>
#include <QBoxLayout>
#include "InfoNotes/datademonstrator.h"
#include <QKeyEvent>

//class WindowManager;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(WindowManager* manager, QWidget *parent = nullptr);
    ~MainWindow();

private:

    HeaderMenu* headerMenu = nullptr;
    QLabel* labelForIcon =  nullptr;
    QIcon logoIcon;
    QHBoxLayout* logoClubAndHeaderLay = nullptr;
    QVBoxLayout* mainLay = nullptr;
    Ui::MainWindow *ui;
    WindowManager* windowManager = nullptr;
    DataDemonstrator* dataDemonstrator = nullptr;

    void createHeaderMenu();
    void createDataDemonstrator();
    friend class WindowManager;
    void keyPressEvent(QKeyEvent *event);
};
#endif // MAINWINDOW_H
