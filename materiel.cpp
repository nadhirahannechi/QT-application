#include "materiel.h"
#include "ui_materiel.h"

Materiel::Materiel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Materiel)
{
    ui->setupUi(this);
    QPixmap bkgnd("C:/Users/nadhira/Documents/test_database/images/plage.jfif");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);



    /* create filter */
     proxyMateriel= new  QSortFilterProxyModel(this);
     proxyMateriel->setSourceModel(afficher());
     proxyMateriel->setFilterCaseSensitivity(Qt::CaseInsensitive);
     ui->comboBox->addItems(QStringList() <<"Code");
     ui->etat->addItems(QStringList() <<"Disponible"<<"Occupé"<<"En panne");



     ui->tableView->setModel(proxyMateriel);
     ui->tableView->resizeColumnsToContents();
     ui->tableView->resizeRowsToContents();

     ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
     ui->cmb->setModel(proxyMateriel);
     ui->combo2->setModel(proxyMateriel);



}

Materiel::~Materiel()
{
    delete ui;
}

QSqlQueryModel* Materiel::afficher()
{
    QSqlQueryModel* model =new QSqlQueryModel();
    model->setQuery("select materiel.code_barre,materiel.date_acq,materiel.type,etat.etat,materiel.marque from materiel,etat where materiel.code_barre=etat.code_barre");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("CODE"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("DATE"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("TYPE"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("ETAT"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("MARQUE"));
 return model;


}


bool Materiel::ajouter()
{
    QSqlQuery query;
    QString res= QString::number(code);
    QString code =ui->codeLine->text();
    QString  date=ui->date->text();
    QString  type=ui->etatLine->text();
    QString  marque=ui->marqueLine->text();
    query.prepare("INSERT INTO materiel (code_barre,date_acq,type,marque) VALUES ('"+code+"','"+date+"','"+type+"','"+marque+"')");


 return query.exec();
}




void Materiel::on_filter_line_textChanged(const QString& arg1)
{

   proxyMateriel->setFilterFixedString(arg1);

}


void Materiel::on_comboBox_currentIndexChanged(int index)
{
    proxyMateriel->setFilterKeyColumn(index);
}

void Materiel::on_Submit_clicked()
{
 bool test=ajouter();
 if(test)
  {

      QSqlQuery query;
      QString res= QString::number(code);
      QString code =ui->codeLine->text();
      QString etat=ui->etat->currentText();
      query.prepare("INSERT INTO etat (code_barre,etat) VALUES ('"+code+"','"+etat+"')");
      query.exec();
      ui->tableView->setModel(afficher());//refresh
      ui->cmb->setModel(afficher());//refresh
      ui->combo2->setModel(afficher());//refresh

      QMessageBox::critical(this,tr("Succes"),tr(" Materiel est sauvgardé"));

    }
  else
   {
    QMessageBox::critical(this,tr("Error"),tr("Ajout n'est pas valide!"));
    }
}

void Materiel::on_cmb_currentIndexChanged(const QString & arg1)
{
  QString id =ui->cmb->currentText();
  QSqlQuery query;
  query.prepare("select *from materiel where code_barre='"+id+"'");


   if(query.exec())
   {
       while(query.next())
       {
         ui->dateEdit->setText(query.value(1).toString());
         ui->etatLine_4->setText(query.value(2).toString());
         ui->marqueLine_5->setText(query.value(3).toString());
       }
   }
}

void Materiel::on_Submit_5_clicked()
{


    QString code =ui->cmb->currentText();
    QString date=ui->dateEdit->text();
    QString type=ui->etatLine_4->text();
    QString marque=ui->marqueLine_5->text();
    QSqlQuery query;
    query.prepare("UPDATE materiel SET code_barre='"+code+"',date_acq='"+date+"',type='"+type+"',marque='"+marque+"' where code_barre='"+code+"'");
    if(query.exec())
    {
        ui->tableView->setModel(afficher());

        QMessageBox::critical(this,tr("Succes"),tr("Modification de materiel!"));
    }
    else
    {
        QMessageBox::critical(this,tr("Error"),tr("Modification n'est pas valide!"));
    }

}





void Materiel::on_pushButton_clicked()
{
    this->hide();
    CMenu menu ;
    menu.setModal(true);
    menu.exec();
}

void Materiel::on_pushButton_2_clicked()
{
    QString id =ui->combo2->currentText();
     QSqlQuery query;
     query.prepare("delete from materiel where code_barre='"+id+"'");
     if(query.exec())
        {
         ui->tableView->setModel(afficher());
         ui->cmb->setModel(afficher());//refresh
         ui->combo2->setModel(afficher());//refresh

          QMessageBox::critical(this,tr("Succes"),tr("Suppression materiel!"));
     }
     else
     {
         QMessageBox::critical(this,tr("Error"),tr("Suppression n'est pas valide!"));
     }

}
