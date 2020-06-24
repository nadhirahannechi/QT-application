#ifndef MATERIEL_H
#define MATERIEL_H
#include <QtSql>
#include <QDialog>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSortFilterProxyModel>
#include <QMessageBox>
#include "menu.h"
namespace Ui {
class Materiel;
}

class Materiel : public QDialog
{
    Q_OBJECT

public:
    explicit Materiel(QWidget *parent = nullptr);
    QSortFilterProxyModel* proxyMateriel;
    QSqlQueryModel* afficher();
    int getCode(){return code;}
    //QTime getDate(){return date_Acq;}
    QString getType(){return type;}
    QString getMarque(){return marque;}
    ~Materiel();

    bool ajouter();
    bool modifier();
    void rechercher(QString);
    void supprimer (QString);

private slots:
    void on_filter_line_textChanged(const QString &arg1);



    void on_comboBox_currentIndexChanged(int index);

    void on_Submit_clicked();

    void on_cmb_currentIndexChanged(const QString &arg1);

    void on_Submit_5_clicked();

    void on_comboBox_2_currentTextChanged(const QString &arg1);

    void on_Submit_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
     Ui::Materiel *ui;
     int code ;
     QString date_Acq ;
     QString etat;
     QString type;
     QString marque ;


};

#endif // MATERIEL_H
