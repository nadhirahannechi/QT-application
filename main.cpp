#include "mainwindow.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QApplication>
#include <QMessageBox>
#include <QtDebug>
#include "connection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Connection c;
    try {
       c.createconnect();
       w.show();
    } catch(QString s) {
        qDebug()<<s;
    }



    return a.exec();
}
