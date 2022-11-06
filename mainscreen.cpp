#include "mainscreen.h"
#include "ui_mainscreen.h"
#include "login.h"

mainscreen::mainscreen(QString user, int admin, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainscreen)
{
    ui->setupUi(this);
    ui->welcomeLabel->setText("Welcome, "+user); //greet the user with the first name we got from the db

    //if the user is not an admin, hide admin function buttons
    if (admin == 0)
    {
        ui->maintainUsersButton->hide();
        ui->maintainUsersLabel->hide();
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
    login *l = new login(this);
    l->show();
}

