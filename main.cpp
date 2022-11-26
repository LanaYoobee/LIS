#include "login.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    login w;

    //connect to the database and open it
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../LIS/db.sqlite");

    if(!db.open())
    {
        qDebug()<<"problem opening database";
    }

    w.show();
    return a.exec();
}
