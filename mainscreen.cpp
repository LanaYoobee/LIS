#include "mainscreen.h"
#include "ui_mainscreen.h"
#include "login.h"
#include "browse.h"

mainscreen::mainscreen(QString user, int admin, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainscreen)
{
    ui->setupUi(this);
    ui->welcomeLabel->setText("Welcome, "+user+"!"); //greet the user with the first name we got from the db

    //if the user is not an admin, hide admin function buttons
    if (admin == 0)
    {
        ui->maintainUsersButton->hide();
        ui->maintainUsersLabel->hide();
        ui->maintainBooksButton->hide();
        ui->maintainBooksLabel->hide();
    }
}

mainscreen::~mainscreen()
{
    delete ui;
}


//the back button on the main screen logs out the user and brings up the login screen again.
void mainscreen::on_quitButton_clicked()
{
    this->hide();
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
    login *l = new login(this);
    l->show();
}


void mainscreen::on_maintainUsersButton_clicked()
{

}


void mainscreen::on_maintainBooksButton_clicked()
{

}


//open the browse catalogue window
void mainscreen::on_browseCatalogueButton_clicked()
{
    browse *b = new browse(this);
    b->show();
}


void mainscreen::on_searchBookButton_clicked()
{

}


void mainscreen::on_viewOwnAccountButton_clicked()
{

}

