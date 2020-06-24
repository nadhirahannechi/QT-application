#ifndef STOCK_H
#define STOCK_H

#include <QDialog>
#include <QtSql>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include "users.h"
namespace Ui {
class Stock;
}

class Stock : public QDialog
{
    Q_OBJECT

public:
    explicit Stock(QWidget *parent = nullptr);
    QSqlQueryModel* afficher();
    ~Stock();



private slots:
    void on_pushButton_clicked();

private:
    Ui::Stock *ui;
};

#endif // STOCK_H
