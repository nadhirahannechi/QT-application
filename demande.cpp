#include "demande.h"
#include "ui_demande.h"

Demande::Demande(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Demande)
{
    ui->setupUi(this);
    ui->tableView->setModel(afficher());
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QPixmap bkgnd("C:/Users/nadhira/Documents/test_database/images/plage.jfif");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
     ui->code->setModel(afficher());
     // Combo box de type
     QSqlQueryModel* modelEtat =new QSqlQueryModel();
     modelEtat->setQuery("select DISTINCT type from materiel");
     ui->type->setModel(modelEtat);
}

Demande::~Demande()
{
    delete ui;
}

 QSqlQueryModel* Demande::afficher()
{
  QSqlQueryModel* model =new QSqlQueryModel();
   model->setQuery("select code_barre,type, marque from materiel");
   model->setHeaderData(0,Qt::Horizontal,QObject::tr("CODE"));
   model->setHeaderData(1,Qt::Horizontal,QObject::tr("TYPE"));
   model->setHeaderData(2,Qt::Horizontal,QObject::tr("MARQUE"));
return model;


}

 bool Demande::ajouter()
 {
 QSqlQuery query;
 QString res= QString::number(code);
 QString cin =ui->lineEdit_2->text();
 QString code =ui->code->currentText();
 QString type=ui->type->currentText();
 QString date_demande=ui->dateEdit->text();
 QString periode=ui->dateEdit_2->text();

 query.prepare("INSERT INTO demande (cin,code,type,date_demande,periode) VALUES ('"+cin+"','"+code+"','"+type+"','"+date_demande+"','"+periode+"')");

  return query.exec();

 }
void Demande::on_pushButton_clicked()
{
    QSqlQuery query3;
    bool test=ajouter();
    QString code =ui->code->currentText();
    QString etatActuelle;
    query3.exec("SELECT etat FROM etat WHERE code_barre = '"+code+"'");
       if (query3.next()) {
            etatActuelle= query3.value(0).toString();
       }
          if((test) && ((etatActuelle=="Disponible")||(etatActuelle=="disponible")))
          {

            ui->tableView->setModel(afficher());

            QMessageBox::critical(this,tr("Save"),tr("Demande sauvgardé"));
           }
           else
           {
               QMessageBox::critical(this,tr("Error"),tr("Materiel reservé deja"));
           }



}










void Demande::on_pushButton_2_clicked()
{
    this->hide();
    Menu_user menu ;
    menu.setModal(true);
    menu.exec();
}
