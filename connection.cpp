#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{
    bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("test");
    db.setUserName("nadhira");
    db.setPassword("nadhira");

    if (db.open())
       test=true;
    else  throw QString ("Erreur Paramétres"+test);
    return  test;
}


