#ifndef EMPLOYE_H
#define EMPLOYE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class employe
{
public:
    employe();
    employe(int,QString,QString);
    QString get_nom();
    QString get_prenom();
    int get_id();
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(QString);
private:
    QString id,name,prenom,login_user,motPasse,poste;

};

#endif // EMPLOYE_H
