#ifndef FOURNISSEUR_H
#define FOURNISSEUR_H
#define MATERIEL_H
#include <QtSql>
#include <QDialog>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSortFilterProxyModel>
#include <QMessageBox>
#include "menu.h"
#include <QDialog>

namespace Ui {
class Fournisseur;
}

class Fournisseur : public QDialog
{
    Q_OBJECT

public:
    explicit Fournisseur(QWidget *parent = nullptr);
    QSortFilterProxyModel* proxyMateriel;
    QSqlQueryModel* afficher();
    bool ajouter();
    bool modifier();
    void rechercher(QString);
    void supprimer (QString);
    ~Fournisseur();

private slots:
    void on_pushButton_clicked();

    void on_filter_line_textChanged(const QString &arg1);

    void on_comboBox_currentIndexChanged(int index);

    void on_Submit_clicked();

    void on_Submit_5_clicked();

    void on_pushButton_2_clicked();

    void on_cmb_currentTextChanged(const QString &arg1);

private:
    Ui::Fournisseur *ui;
};

#endif // FOURNISSEUR_H
