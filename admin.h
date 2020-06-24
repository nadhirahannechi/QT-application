#ifndef ADMIN_H
#define ADMIN_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Admin
{
public:
    Admin();
    Admin(int,QString,QString);
    QString get_nom();
    QString get_prenom();
    int get_id();
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
private:
    QString username,password;

};

#endif // ADMIN_H
