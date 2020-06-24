#ifndef MENU_USER_H
#define MENU_USER_H

#include <QDialog>
#include "demande.h"
#include "reclamation.h"
#include "demande.h"
namespace Ui {
class Menu_user;
}

class Menu_user : public QDialog
{
    Q_OBJECT

public:
    explicit Menu_user(QWidget *parent = nullptr);
    ~Menu_user();

private slots:
    void on_stk_clicked();

    void on_reclamation_clicked();

    void on_reservation_clicked();

private:
    Ui::Menu_user *ui;
};

#endif // MENU_USER_H
