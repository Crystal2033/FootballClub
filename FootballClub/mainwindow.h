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

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow, public InterfaceObserver
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    DataBase* database = nullptr;
    HeaderMenu* headerMenu = nullptr;
    QVBoxLayout* mainLay = nullptr;
    Ui::MainWindow *ui;
    void updateByObserver(const REQUEST_TYPE requestStatus) override;

    bool connectToDatabase();
    void createHeaderMenu();
};
#endif // MAINWINDOW_H
