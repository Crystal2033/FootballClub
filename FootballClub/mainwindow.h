/***************************************************************************
 *                                                                         *
 *   Copyright (C) 09.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "DataBase/database.h"
#include "Menu/headermenu.h"
#include <QMainWindow>
#include <QBoxLayout>

class WindowManager;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(WindowManager* manager ,QWidget *parent = nullptr);
    ~MainWindow();

private:
    DataBase* database = nullptr;
    HeaderMenu* headerMenu = nullptr;
    QVBoxLayout* mainLay = nullptr;
    Ui::MainWindow *ui;
    WindowManager* windowManager = nullptr;


    bool connectToDatabase();
    void createHeaderMenu();

    friend class WindowManager;
};
#endif // MAINWINDOW_H
