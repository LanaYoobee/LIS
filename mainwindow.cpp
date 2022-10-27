#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qtbcrypt.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_passwordEntry_returnPressed()
{
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../LIS/db.sqlite");

    if(!db.open())
    {
        qDebug()<<"problem opening database";
    }

    QSqlQuery qry;
    QString username, enteredPassword, user, admin, storedPassword, storedSalt;

    username = ui->usernameEntry->text();
    enteredPassword = ui->passwordEntry->text();

    qry.prepare("select username, password, salt, admin from users where username= :username");
    qry.bindValue(":username", username);
    qry.exec();

    if(!qry.first())
    {
        QMessageBox::critical(this, "LIS", "Incorrect username or password");
    }
    else
    {
        user = qry.value(0).toString();
        storedPassword = qry.value(1).toString();
        storedSalt = qry.value(2).toString();

        QString hashedPassword = QtBCrypt::hashPassword(enteredPassword, storedSalt);
        if (hashedPassword == storedPassword)
        {
            admin = qry.value(3).toString();
            if (admin=="Y")
            {
                this->hide();
                QMessageBox::information(this, "Log In Admin User","Welcome, "+user);
            }
            else if (admin=="N")
            {

                this->hide();
                QMessageBox::information(this, "Log In Normal User","Welcome, "+user);
            }
        }
        else QMessageBox::critical(this, "LIS", "Incorrect username or password");
    }

}


//void MainWindow::on_pushButton_clicked()

//{

//    QSqlDatabase db;
//    db = QSqlDatabase::addDatabase("QSQLITE");
//    db.setDatabaseName("../LIS/db.sqlite");

//    if(!db.open())
//    {
//        qDebug()<<"problem opening database";
//    }

//    QSqlQuery qry;
//    QString salt = QtBCrypt::generateSalt();
//    QString hashedPassword = QtBCrypt::hashPassword("sillyPassword", salt);

//    qry.prepare("INSERT INTO users(ID, username, password, salt, first_name, surname, phone, admin) VALUES(1,'newUser',:password,:salt,'Admin','secondAdmin',1232132,'Y');");
//    qry.bindValue(":password", hashedPassword);
//    qry.bindValue(":salt", salt);
//    qry.exec();

//}

