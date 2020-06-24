#include "menu.h"
#include "ui_menu.h"

CMenu::CMenu(QWidget *parent) :
    QDialog(parent), ui(new Ui::CMenu)
{
     ui->setupUi(this);
     QPixmap bkgnd("C:/Users/nadhira/Documents/test_database/images/plage.jfif");
     bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
     QPalette palette;
     palette.setBrush(QPalette::Background, bkgnd);
     this->setPalette(palette);
}
CMenu::~CMenu()
{
 delete ui;
}

void CMenu::on_mtr_clicked()
{
    this->hide();
    Materiel materiel ;
    materiel.setModal(true);
    materiel.exec();
}

void CMenu::on_stk_clicked()
{
    this->hide();
    Reservation reser ;
    reser.setModal(true);
    reser.exec();
}

void CMenu::on_mtnc_clicked()
{
    this->hide();
    Maintenance maintenance ;
    maintenance.setModal(true);
    maintenance.exec();
}

void CMenu::on_utilisateur_clicked()
{
    this->hide();
    Users user ;
    user.setModal(true);
    user.exec();
}

void CMenu::on_pushButton_clicked()
{

}

void CMenu::on_mtr_2_clicked()
{
    this->hide();
    Fournisseur fournisseur ;
    fournisseur.setModal(true);
    fournisseur.exec();
}
