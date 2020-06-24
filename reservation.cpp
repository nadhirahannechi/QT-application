#include "reservation.h"
#include "ui_reservation.h"

Reservation::Reservation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Reservation)
{
    ui->setupUi(this);
    QPixmap bkgnd("C:/Users/nadhira/Documents/test_database/images/plage.jfif");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    ui->tableView_2->setModel(afficher());
    ui->tableView_2->resizeColumnsToContents();
    ui->tableView_2->resizeRowsToContents();

    ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    /* create filter */
     proxyMateriel= new  QSortFilterProxyModel(this);
     proxyMateriel->setSourceModel(afficherReser());
     proxyMateriel->setFilterCaseSensitivity(Qt::CaseInsensitive);
     ui->comboBox->addItems(QStringList() <<"Nom"<<"Prénon"<<"Poste");




     ui->tableView->setModel(proxyMateriel);
     ui->tableView->resizeColumnsToContents();
     ui->tableView->resizeRowsToContents();

     ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
     QSqlQueryModel* modelCode =new QSqlQueryModel();
     modelCode->setQuery("select code_barre  from reservation");
     ui->comboBox_2->setModel(modelCode);
}

Reservation::~Reservation()
{
    delete ui;
}
QSqlQueryModel* Reservation::afficher()
{
   QSqlQueryModel* model =new QSqlQueryModel();
    model->setQuery("select demande.code,cin,etat.etat,demande.date_demande,demande.periode,demande.type from materiel,demande,etat where materiel.code_barre=demande.code AND materiel.code_barre=etat.code_barre AND ((etat.etat='Disponible') OR (etat.etat='disponible'))");

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("CODE"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("CIN"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("ETAT"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Date demande"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Date reservation"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("TYPE"));


 return model;


}
QSqlQueryModel* Reservation::afficherReser()
{
   QSqlQueryModel* model =new QSqlQueryModel();
    model->setQuery("select name,prenon,poste,periode,type,marque from employe,reservation,materiel where reservation.code_barre=materiel.code_barre AND reservation.user_id=employe.id ");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Prénon"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Poste"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Période"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Type"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Marque"));



 return model;


}
void Reservation::on_pushButton_clicked()
{
    QSqlQuery query ,query2,query3,query4;
    QString res= QString::number(code);
    QString  etatActuelle;
    QString code =ui->code->text();
    QString  cin=ui->cin->text();
    QString   etat=ui->etat->text();
    QString  periode=ui->periode->text();
    query3.exec("SELECT etat FROM etat WHERE code_barre = '"+code+"'");
       if (query3.next()) {
            etatActuelle= query3.value(0).toString();
       }
       if((etatActuelle=="Disponible") || (etatActuelle=="disponible"))
           {
            query.prepare("INSERT INTO reservation (user_id,code_barre,periode) VALUES ('"+cin+"','"+code+"','"+periode+"')");
            query2.prepare("UPDATE etat SET etat='"+etat+"' where code_barre='"+code+"'");
            query.exec();
            query2.exec();
            query4.prepare("delete from demande where code='"+code+"'");
            query4.exec();
            ui->tableView->setModel(afficherReser());
            ui->tableView_2->setModel(afficher());

            //refresh comboBox
             QSqlQueryModel* modelCode =new QSqlQueryModel();
            modelCode->setQuery("select code_barre  from reservation");
            ui->comboBox_2->setModel(modelCode);
            QMessageBox::critical(this,tr("Save"),tr("Reserved"));
            }





             else
             {
                   QMessageBox::critical(this,tr("Error"),tr("verify please"));
            }



}

void Reservation::on_pushButton_2_clicked()
{
    this->hide();
    CMenu menu ;
    menu.setModal(true);
    menu.exec();
}

void Reservation::on_comboBox_currentIndexChanged(int index)
{
proxyMateriel->setFilterKeyColumn(index);

}

void Reservation::on_filter_line_2_textChanged(const QString& arg1)
{
   proxyMateriel->setFilterFixedString(arg1);
}

void Reservation::on_Submit_2_clicked()
{
    QString id =ui->comboBox_2->currentText();
    QSqlQuery query,query2;
    query.prepare("delete from reservation where code_barre='"+id+"'");
    if(query.exec())
       {

         ui->tableView->setModel(afficherReser());
         query2.prepare("UPDATE etat SET etat='disponible' where code_barre='"+id+"'");
         query2.exec();
         if(query2.exec())
         {
             //refresh comboBox
             QSqlQueryModel* modelCode =new QSqlQueryModel();
             modelCode->setQuery("select reservation.code_barre  from reservation,etat where reservation.code_barre=etat.code_barre AND etat.etat='occupé'");
             ui->comboBox_2->setModel(modelCode);
             QMessageBox::critical(this,tr("Succes"),tr("Anuller la reservation!"));
         }
    }
    else
    {
        QMessageBox::critical(this,tr("Error"),tr("Anullation n'est pas valide!"));
    }
}
