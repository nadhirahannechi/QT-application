#ifndef MAINTENANCE_H
#define MAINTENANCE_H
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSortFilterProxyModel>
#include <QSortFilterProxyModel>
#include <QMessageBox>
#include "menu.h"

namespace Ui {
class Maintenance;
}

class Maintenance : public QDialog
{
    Q_OBJECT

public:
    explicit Maintenance(QWidget *parent = nullptr);
    QSortFilterProxyModel* proxyMateriel;
    QSqlQueryModel* afficher();
    QSqlQueryModel* afficherRec();
    ~Maintenance();

private slots:
    void on_filter_line_2_textChanged(const QString &arg1);

    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_clicked();

    void on_Submit_2_clicked();

    void on_Submit_3_clicked();

private:
    Ui::Maintenance *ui;
    int code;
    QString probleme;

};

#endif // MAINTENANCE_H
