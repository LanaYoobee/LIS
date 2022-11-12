#include "db_connect.h"

//reusable class for connecting to the database

db_connect::db_connect(QObject *parent)
    : QObject{parent}
{
    //connect to the database and open it
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../LIS/db.sqlite");

    if(!db.open())
    {
        qDebug()<<"problem opening database";
    }
}
