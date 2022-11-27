#include "mainscreen.h"
#include "ui_mainscreen.h"
#include "browse.h"
#include "maintainusers.h"
#include "searchbooks.h"
#include "viewaccount.h"

mainscreen::mainscreen(QString user, int admin, int user_id, login *parent) :
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

   this->admin = admin;
   this->user = user;
   this->user_id = user_id;
   this->parent = parent;
}


mainscreen::~mainscreen()
{
    delete ui;
}


//the back button brings up the login screen again.
void mainscreen::on_quitButton_clicked()
{
    this->close();
    parent->show();
    delete this;
}


void mainscreen::on_maintainUsersButton_clicked()
{
    MaintainUsers *mu = new MaintainUsers(this);
    mu->show();
}

//same functionality as searching for a book as we have to find a book before we can maintain it
void mainscreen::on_maintainBooksButton_clicked()
{
    SearchBooks *sb = new SearchBooks(this);
    sb->show();
}


//open the browse catalogue window
void mainscreen::on_browseCatalogueButton_clicked()
{
    browse *b = new browse("browse", "", this);
    b->show();
}


void mainscreen::on_searchBookButton_clicked()
{
    SearchBooks *sb = new SearchBooks(this);
    sb->show();
}


void mainscreen::on_viewOwnAccountButton_clicked()
{
    ViewAccount *va = new ViewAccount(user_id, this);
    va->show();
}

