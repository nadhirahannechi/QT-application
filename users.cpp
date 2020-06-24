#include "users.h"
#include "ui_users.h"

Users::Users(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Users)
{
    ui->setupUi(this);
    //bACKGROUND IMAGE
    QPixmap bkgnd("C:/Users/nadhira/Documents/test_database/images/plage.jfif");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    //Make filter in tableView

      proxyMateriel= new  QSortFilterProxyModel(this);
      proxyMateriel->setSourceModel(afficher());
      proxyMateriel->setFilterCaseSensitivity(Qt::CaseInsensitive);
      ui->cmd->addItems(QStringList() <<"ID"<<"Nom"<<"Prénom");




     ui->tableView_2->setModel(proxyMateriel);
     ui->tableView_2->resizeColumnsToContents();
     ui->tableView_2->resizeRowsToContents();

     ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

      ui->cmb_2->setModel(proxyMateriel);
      ui->comboBox_4->setModel(afficher());



}
QSqlQueryModel* Users::afficher()
{
    QSqlQueryModel* model =new QSqlQueryModel();
    model->setQuery("select * from employe ");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prénom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Login"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Mot de passe"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Poste"));
 return model;


}
bool Users::ajouter()
{
    QSqlQuery query;
    QString id =ui->id->text();
    QString  nom=ui->nom->text();
    QString  prenon=ui->prenon->text();
    QString  login=ui->login->text();
    QString  pass=ui->pass->text();
    QString  poste=ui->poste->text();
    query.prepare("INSERT INTO employe (id,name,prenon,login_user,mot_de_passe,poste) VALUES ('"+id+"','"+nom+"','"+prenon+"','"+login+"','"+pass+"' ,'"+poste+"')");


 return query.exec();
}
bool Users::modifier()
{
    QString id =ui->cmb_2->currentText();
    QString  nom=ui->nom_2->text();
    QString  prenon=ui->prenon_2->text();
    QString  login=ui->login_2->text();
    QString  pass=ui->pass_2->text();
    QString  poste=ui->poste_2->text();
    QSqlQuery query;
    query.prepare("UPDATE employe SET id='"+id+"',name='"+nom+"',prenon='"+prenon+"',login_user='"+login+"',mot_de_passe='"+pass+"',poste='"+poste+"' where id='"+id+"'");


 return query.exec();
}


Users::~Users()
{
    delete ui;
}

void Users::on_filter_line_2_textChanged(const QString& arg1)
{
       proxyMateriel->setFilterFixedString(arg1);
}

void Users::on_Submit_3_clicked()
{
    bool test=ajouter();
    if(test)
     {
         ui->tableView_2->setModel(afficher());//refresh
         ui->cmb_2->setModel(afficher());
         ui->comboBox_4->setModel(afficher());

         QMessageBox::critical(this,tr("Succes"),tr(" Employé est sauvgardé"));

       }
     else
      {
       QMessageBox::critical(this,tr("Error"),tr("Ajout n'est pas valide!"));
       }

}

void Users::on_Submit_6_clicked()
{
    bool test=modifier();
    if(test)
    {
        ui->tableView_2->setModel(afficher());

        QMessageBox::critical(this,tr("Succes"),tr("Modification de employé!"));
    }
    else
    {
        QMessageBox::critical(this,tr("Error"),tr("Modification n'est pas valide!"));
    }
}

void Users::on_cmb_2_currentIndexChanged(const QString &arg1)
{
    QString id =ui->cmb_2->currentText();
    QSqlQuery query;
    query.prepare("select *from employe where id='"+id+"'");


     if(query.exec())
     {
         while(query.next())
         {
           ui->nom_2->setText(query.value(1).toString());
           ui->prenon_2->setText(query.value(2).toString());
           ui->login_2->setText(query.value(3).toString());
           ui->pass_2->setText(query.value(4).toString());
           ui->poste_2->setText(query.value(5).toString());

         }
     }
}

bool Users::supprimer()
{
    QString id =ui->comboBox_4->currentText();
    QSqlQuery query;
    query.prepare("delete from employe where id='"+id+"'");

 return query.exec();
}

void Users::on_Submit_4_clicked()
{ bool test=supprimer();
    if(test)
       {
        ui->tableView_2->setModel(afficher());
        ui->cmb_2->setModel(afficher());
        ui->comboBox_4->setModel(afficher());

         QMessageBox::critical(this,tr("Succes"),tr("Suppression employé!"));
    }
    else
    {
        QMessageBox::critical(this,tr("Error"),tr("Suppression n'est pas valide!"));
    }
}



void Users::on_comboBox_3_currentIndexChanged(int index)
{
     proxyMateriel->setFilterKeyColumn(index);
}


void Users::on_pushButton_clicked()
{
    this->hide();
    CMenu menu ;
    menu.setModal(true);
    menu.exec();
}
