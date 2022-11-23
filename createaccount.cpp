#include "createaccount.h"
#include "ui_createaccount.h"
#include "login.h"
#include "qtbcrypt.h"

CreateAccount::CreateAccount(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CreateAccount)
{
    ui->setupUi(this);
    ui->confirmLabel->hide();
}

CreateAccount::~CreateAccount()
{
    delete ui;
}

void CreateAccount::on_quitButton_clicked()
{
    this->close();
}


void CreateAccount::on_saveAccountButton_clicked()
{
    db_connect();

    QString username, password, name, surname;
    int phone, admin;

    username = ui->usernameLineEdit->text();
    password = ui->passwordLineEdit->text();
    name = ui->nameLineEdit->text();
    surname = ui->surnameLineEdit->text();
    phone = ui->phoneLineEdit->text().toInt();
    admin = ui->checkBox->isChecked();

    QSqlQuery qry;

    qry.prepare("select username from users where username= :username");
    qry.bindValue(":username", username);
    qry.exec();

    if(!qry.first()) //check if there were any results for this username
    {
        QString salt = QtBCrypt::generateSalt();
        QString hashedPassword = QtBCrypt::hashPassword(password, salt);
        qry.prepare("INSERT INTO users(username, password, first_name, surname, phone, admin) VALUES(:username, :password, :first_name, :surname, :phone, :admin);");
        qry.bindValue(":username", username);
        qry.bindValue(":password", hashedPassword);
        qry.bindValue(":first_name", name);
        qry.bindValue(":surname", surname);
        qry.bindValue(":phone", phone);
        qry.bindValue(":admin", admin);
        qry.exec();

        ui->confirmLabel->show();

    }
    else
        QMessageBox::critical(this, "LIS", "Username already taken");

}

