#include "maintenance.h"
#include "ui_maintenance.h"

Maintenance::Maintenance(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Maintenance)
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
     proxyMateriel->setSourceModel(afficherRec());
     proxyMateriel->setFilterCaseSensitivity(Qt::CaseInsensitive);
     ui->comboBox->addItems(QStringList() <<"CODE"<<"TYPE"<<"Etat"<<"Probléme");




     ui->tableView->setModel(proxyMateriel);
     ui->tableView->resizeColumnsToContents();
     ui->tableView->resizeRowsToContents();

     ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
     QSqlQueryModel* modelCode =new QSqlQueryModel();
     modelCode->setQuery("select DISTINCT id_produit from maintenance");
     ui->comboBox_2->setModel(modelCode);


}

Maintenance::~Maintenance()
{
    delete ui;
}
QSqlQueryModel* Maintenance::afficher()
{
    QSqlQueryModel* model =new QSqlQueryModel();
    model->setQuery("select reclamation.id_user,employe.name,materiel.code_barre,reclamation.probleme from reclamation,employe,materiel WHERE reclamation.id_user=employe.id AND reclamation.code_produit=materiel.code_barre");

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NAME"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("CODE"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Probléme"));



 return model;


}
QSqlQueryModel* Maintenance::afficherRec()
{
    QSqlQueryModel* model =new QSqlQueryModel();
    model->setQuery("select maintenance.id_produit,materiel.type,etat.etat,maintenance.probleme from maintenance,materiel,etat where maintenance.id_produit=materiel.code_barre and materiel.code_barre=etat.code_barre");

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("CODE"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("TYPE"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Etat"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Probléme"));




 return model;


}
void Maintenance::on_comboBox_currentIndexChanged(int index)
{
    proxyMateriel->setFilterKeyColumn(index);
}
void Maintenance::on_filter_line_2_textChanged(const QString& arg1)
{
    proxyMateriel->setFilterFixedString(arg1);
}





void Maintenance::on_pushButton_clicked()
{
    QSqlQuery query,query2,query3 ;
    QString res= QString::number(code);
    QString code =ui->code->text();
    QString  probleme=ui->probleme->text();
    QString   etat=ui->etat->text();



          query.prepare("INSERT INTO maintenance (id_produit,probleme) VALUES ('"+code+"','"+probleme+"')");
          if(query.exec())
          {
            query2.prepare("UPDATE etat SET etat='"+etat+"' where code_barre='"+code+"'");

            query3.prepare("delete from reclamation where code_produit='"+code+"'");
            query2.exec();
            query3.exec();
            ui->tableView->setModel(afficherRec());
            ui->tableView_2->setModel(afficher());
            //refresh comboBox
            QSqlQueryModel* modelCode =new QSqlQueryModel();
            modelCode->setQuery("select DISTINCT id_produit from maintenance");
            ui->comboBox_2->setModel(modelCode);
            QMessageBox::critical(this,tr("Save"),tr("Materiel envoyé à la maintenance"));
          }
          else
          {
              QMessageBox::critical(this,tr("Error"),tr("Verify please"));

          }


}


void Maintenance::on_Submit_2_clicked()
{
    QString id =ui->comboBox_2->currentText();
    QSqlQuery query,query2;
    query.prepare("delete from maintenance where id_produit='"+id+"'");
    if(query.exec())
       {

         ui->tableView->setModel(afficherRec());
         query2.prepare("UPDATE etat SET etat='disponible' where code_barre='"+id+"'");
         query2.exec();
         if(query2.exec())
         {
             //refresh comboBox
             QSqlQueryModel* modelCode =new QSqlQueryModel();
             modelCode->setQuery("select DISTINCT id_produit from maintenance");
             ui->comboBox_2->setModel(modelCode);
             QMessageBox::critical(this,tr("Succes"),tr("Materiel en bon etat!"));
         }
    }
    else
    {
        QMessageBox::critical(this,tr("Error"),tr("Merci de verifier!"));
    }
}

void Maintenance::on_Submit_3_clicked()
{
    this->hide();
    CMenu menu ;
    menu.setModal(true);
    menu.exec();
}
