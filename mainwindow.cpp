#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std ;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

       QPixmap bkgnd("C:/Users/nadhira/Documents/test_database/images/plage.jfif");
       bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
       QPalette palette;
       palette.setBrush(QPalette::Background, bkgnd);
       this->setPalette(palette);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Submit_clicked()
{
  QString username,password;
  username=ui->lineEdit_username->text();
  password=ui->lineEdit_Password->text();
  if (ui->checkBox->isChecked())
  {
      QSqlQuery query;
      if(query.exec("select * from login where username='"+username+"' AND password='"+password+"'"))
      {
           int count=0;
           while(query.next())
              { count++;}
           if(count==1)
           {
               this->hide();
               CMenu menu ;
               menu.setModal(true);
               menu.exec();
           }
          /* if(count>1)
           {

         }
           if(count<1)
           {

         }
     */
      }
  }
  else
  {
      QSqlQuery query;
      if(query.exec("select * from employe where login_user='"+username+"' AND mot_de_passe='"+password+"'"))
      {
           int count=0;
           while(query.next())
              { count++;}
           if(count==1)
           {
               this->hide();
               Menu_user menuU ;
               menuU.setModal(true);
               menuU.exec();
           }
        }


  }
}
