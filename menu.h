#ifndef MENU_H
#define MENU_H
#include <QDialog>
#include "materiel.h"
#include "maintenance.h"
#include "users.h"
#include "stock.h"
#include "reservation.h"
#include "mainwindow.h"
#include "fournisseur.h"
namespace Ui {
class CMenu;
}

class CMenu : public QDialog
{
    Q_OBJECT

public:
    explicit CMenu(QWidget *parent = nullptr);
    ~CMenu();

private slots:
    void on_mtr_clicked();

    void on_stk_clicked();

    void on_mtnc_clicked();

    void on_utilisateur_clicked();

    void on_pushButton_clicked();

    void on_mtr_2_clicked();

private:
    Ui::CMenu *ui;
};
#endif // MENU_H
