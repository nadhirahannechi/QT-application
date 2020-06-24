#include "stock.h"
#include "ui_stock.h"

Stock::Stock(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Stock)
{
    ui->setupUi(this);
    ui->tableView->setModel(afficher());

}

Stock::~Stock()
{
    delete ui;
}

QSqlQueryModel* Stock::afficher()
{
    QSqlQueryModel* model =new QSqlQueryModel();
    model->setQuery("select* from login");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("USERNAME"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("PASS"));
 return model;
}

void Stock::on_pushButton_clicked()
{
    this->hide();
    Users user ;
    user.setModal(true);
    user.exec();
}
