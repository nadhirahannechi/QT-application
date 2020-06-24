#include "fournisseur.h"
#include "ui_fournisseur.h"

Fournisseur::Fournisseur(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Fournisseur)
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
     ui->comboBox->addItems(QStringList() <<"Cin"<<"Nom"<<"Prénom"<<"Adresse"<<"Num");




     ui->tableView->setModel(proxyMateriel);
     ui->tableView->resizeColumnsToContents();
     ui->tableView->resizeRowsToContents();

     ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
     ui->cmb->setModel(proxyMateriel);
     ui->combo2->setModel(proxyMateriel);


}

Fournisseur::~Fournisseur()
{
    delete ui;
}
QSqlQueryModel* Fournisseur::afficher()
{
    QSqlQueryModel* model =new QSqlQueryModel();
    model->setQuery("select * from fournisseur");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prénom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Adresse"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Num"));
 return model;


}


bool Fournisseur::ajouter()
{
    QSqlQuery query;
    QString cin =ui->cin->text();
    QString  nom=ui->nom->text();
    QString  prenom=ui->prenom->text();
    QString  adresse=ui->adresse->text();
    QString  num=ui->num->text();
    query.prepare("INSERT INTO fournisseur (cin,nom,prenom,adresse,num) VALUES ('"+cin+"','"+nom+"','"+prenom+"','"+adresse+"','"+num+"')");


 return query.exec();
}

void Fournisseur::on_pushButton_clicked()
{
    this->hide();
    CMenu menu ;
    menu.setModal(true);
    menu.exec();
}

void Fournisseur::on_filter_line_textChanged(const QString& arg1)
{
    proxyMateriel->setFilterFixedString(arg1);

}

void Fournisseur::on_comboBox_currentIndexChanged(int index)
{
 proxyMateriel->setFilterKeyColumn(index);
}

void Fournisseur::on_Submit_clicked()
{
    bool test=ajouter();
    if(test)
     {

         ui->tableView->setModel(afficher());//refresh
         ui->cmb->setModel(afficher());//refresh
         ui->combo2->setModel(afficher());//refresh

         QMessageBox::critical(this,tr("Succes"),tr(" Fournisseur est sauvgardé"));

       }
     else
      {
       QMessageBox::critical(this,tr("Error"),tr("Ajout n'est pas valide!"));
       }

}

void Fournisseur::on_Submit_5_clicked()
{

    QString cin =ui->cmb->currentText();
    QString nom=ui->nom_2->text();
    QString prenom=ui->prenom_2->text();
    QString adresse=ui->adresse_2->text();
    QString num=ui->num_2->text();
    QSqlQuery query;
    query.prepare("UPDATE fournisseur SET cin='"+cin+"',nom='"+nom+"',prenom='"+prenom+"',adresse='"+adresse+"',num='"+num+"' where cin='"+cin+"'");
    if(query.exec())
    {
        ui->tableView->setModel(afficher());

        QMessageBox::critical(this,tr("Succes"),tr("Modification de fournisseur!"));
    }
    else
    {
        QMessageBox::critical(this,tr("Error"),tr("Modification n'est pas valide!"));
    }

}

void Fournisseur::on_pushButton_2_clicked()
{
    QString cin =ui->combo2->currentText();
     QSqlQuery query;
     query.prepare("delete from fournisseur where cin='"+cin+"'");
     if(query.exec())
        {
         ui->tableView->setModel(afficher());
         ui->cmb->setModel(afficher());//refresh
         ui->combo2->setModel(afficher());//refresh

          QMessageBox::critical(this,tr("Succes"),tr("Suppression fournisseur!"));
     }
     else
     {
         QMessageBox::critical(this,tr("Error"),tr("Suppression n'est pas valide!"));
     }
}

void Fournisseur::on_cmb_currentTextChanged(const QString& arg1)
{
    QString cin =ui->cmb->currentText();
    QSqlQuery query;
    query.prepare("select *from fournisseur where cin='"+cin+"'");


     if(query.exec())
     {
         while(query.next())
         {
           ui->nom_2->setText(query.value(1).toString());
           ui->prenom_2->setText(query.value(2).toString());
           ui->adresse_2->setText(query.value(3).toString());
           ui->num_2->setText(query.value(4).toString());
         }
     }
}
