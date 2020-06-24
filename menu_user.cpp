#include "menu_user.h"
#include "ui_menu_user.h"

Menu_user::Menu_user(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Menu_user)
{
    ui->setupUi(this);
    QPixmap bkgnd("C:/Users/nadhira/Documents/test_database/images/plage.jfif");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
}

Menu_user::~Menu_user()
{
    delete ui;
}



void Menu_user::on_reclamation_clicked()
{
    this->hide();
    Reclamation reclamation ;
    reclamation.setModal(true);
    reclamation.exec();
}

void Menu_user::on_reservation_clicked()
{
    this->hide();
    Demande demande ;
    demande.setModal(true);
    demande.exec();
}
