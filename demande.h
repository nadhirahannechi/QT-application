#ifndef DEMANDE_H
#define DEMANDE_H

#include <QDialog>
#include "QSqlQueryModel"
#include <QSqlQuery>
#include <QMessageBox>
#include "menu_user.h"


namespace Ui {
class Demande;
}

class Demande : public QDialog
{
    Q_OBJECT

public:
    explicit Demande(QWidget *parent = nullptr);
    QSqlQueryModel* afficher();
    bool ajouter();
    bool modifier();
    void rechercher(QString);
    void supprimer (QString);
    ~Demande();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Demande *ui;
    QString cin;
    int code ;
    QString type;
    QString date_demande;
    QString periode;
};

#endif // DEMANDE_H
