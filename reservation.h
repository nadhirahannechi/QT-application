#ifndef RESERVATION_H
#define RESERVATION_H

#include <QDialog>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSortFilterProxyModel>
#include <QSortFilterProxyModel>
#include <QMessageBox>
#include "menu.h"
namespace Ui {
class Reservation;
}

class Reservation : public QDialog
{
    Q_OBJECT

public:
    explicit Reservation(QWidget *parent = nullptr);
    QSortFilterProxyModel* proxyMateriel;
    ~Reservation();

private slots:
    void on_pushButton_clicked();


    void on_pushButton_2_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_filter_line_2_textChanged(const QString &arg1);

    void on_Submit_2_clicked();

private:
    Ui::Reservation *ui;
    int code;
    QSqlQueryModel* afficher();

    QSqlQueryModel* afficherReser();
};

#endif // RESERVATION_H
