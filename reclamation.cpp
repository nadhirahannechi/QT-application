#include "reclamation.h"
#include "ui_reclamation.h"

Reclamation::Reclamation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Reclamation)
{
    ui->setupUi(this);
    QPixmap bkgnd("C:/Users/nadhira/Documents/test_database/images/plage.jfif");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);


    QSqlQueryModel* modelCode =new QSqlQueryModel();
    modelCode->setQuery("select code_barre  from reservation");
    ui->code->setModel(modelCode);

}

Reclamation::~Reclamation()
{
    delete ui;
}

void Reclamation::on_pushButton_2_clicked()
{
    this->hide();
    Menu_user  menu ;
    menu.setModal(true);
    menu.exec();
}
bool Reclamation::ajouter()
{
QSqlQuery query;
QString res= QString::number(code);
QString cin =ui->cin->text();
QString code =ui->code->currentText();
QString date=ui->date->text();
QString probleme=ui->probleme->toPlainText();

query.prepare("INSERT INTO reclamation (id_user,code_produit,date_reservation,probleme) VALUES ('"+cin+"','"+code+"','"+date+"','"+probleme+"')");

 return query.exec();

}
void Reclamation::on_pushButton_clicked()
{

    bool test=ajouter();
    QString cin =ui->cin->text();
    QString code =ui->code->currentText();
    QSqlQuery query;
    QString coderes;
    query.exec("SELECT user_id FROM reservation WHERE code_barre = '"+code+"'");
       if (query.next()) {
           coderes = query.value(0).toString();

       }
          if((test) && (coderes==cin))
          {


            QMessageBox::critical(this,tr("Save"),tr("Réclamation sauvgardé"));
           }
           else
           {
               QMessageBox::critical(this,tr("Error"),tr("Materiel reservé deja par un autre employe"));
           }



}
