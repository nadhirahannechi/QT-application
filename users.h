#ifndef USERS_H
#define USERS_H

#include <QtSql>
#include <QDialog>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSortFilterProxyModel>
#include <QMessageBox>
#include "menu.h"

namespace Ui {
class Users;
}

class Users : public QDialog
{
    Q_OBJECT

public:
    explicit Users(QWidget *parent = nullptr);
    QSqlQueryModel* afficher();
    QSortFilterProxyModel* proxyMateriel;
    bool ajouter();
    bool modifier();
    void rechercher(QString);
    bool supprimer ();

    ~Users();

private slots:
    void on_filter_line_2_textChanged(const QString &arg1);

    void on_Submit_3_clicked();

    void on_Submit_6_clicked();

    void on_cmb_2_currentIndexChanged(const QString &arg1);

    void on_Submit_4_clicked();

    void on_comboBox_3_currentIndexChanged(const QString &arg1);

    void on_comboBox_3_currentIndexChanged(int index);

    void on_pushButton_clicked();

private:
    Ui::Users *ui;
private:
    QString id,name,prenom,login_user,motPasse,poste;

};

#endif // USERS_H
