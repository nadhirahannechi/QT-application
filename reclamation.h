#ifndef RECLAMATION_H
#define RECLAMATION_H

#include <QDialog>
#include "menu_user.h"

namespace Ui {
class Reclamation;
}

class Reclamation : public QDialog
{
    Q_OBJECT

public:
    explicit Reclamation(QWidget *parent = nullptr);
    ~Reclamation();
    bool ajouter();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::Reclamation *ui;
    QString cin;
    int code ;
    QString probleme;
    QString date_reservation;

};

#endif // RECLAMATION_H
