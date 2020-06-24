#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include<QDebug>
#include <QFileInfo>
#include "materiel.h"
#include <QSqlQuery>
#include <iostream>
#include "connection.h"
#include <QMessageBox>
#include "menu.h"
#include "users.h"
#include "demande.h"
#include "menu_user.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Submit_clicked();


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
