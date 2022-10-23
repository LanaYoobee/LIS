#include "mainwindow.h"
#include "ui_mainwindow.h"


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
    QString username, password, user, admin;

    username = ui->usernameEntry->text();
    password = ui->passwordEntry->text();

    qry.prepare("select username, first_name, admin from users where username= :username and password = :password");
    qry.bindValue(":username", username);
    qry.bindValue(":password", password);
    qry.exec();

    while(qry.next())
    {
        user = qry.value(1).toString();
        admin = qry.value(2).toString();
    }
    if (admin=="Y")
    {
        //            ui->label->setText("Hi "+user+", you're an admin");
        this->hide();
        QMessageBox::information(this, "Log In Normal User","Welcome, "+user);
    }
    else if (admin=="N")
    {

       // this->hide();
        QMessageBox::information(this, "Log In Normal User","Welcome, "+user);
    }
    else
    {
        QMessageBox::critical(this, "LIS", "Incorrect username or password");

    }


}

