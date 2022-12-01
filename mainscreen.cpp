#include "mainscreen.h"
#include "ui_mainscreen.h"
#include "browse.h"
#include "maintainusers.h"
#include "searchbooks.h"
#include "viewaccount.h"

mainscreen::mainscreen(QString userFirstName, int admin, int loggedInUserID, login *parent) :
    QDialog(parent),
    ui(new Ui::mainscreen)
{
    ui->setupUi(this);

    ui->welcomeLabel->setText("Welcome, "+userFirstName+"!"); //greet the user with the first name we got from the db

    //if the user is not an admin, hide admin function buttons
    if (admin != 1)
    {
        ui->maintainUsersButton->hide();
        ui->maintainUsersLabel->hide();
        ui->maintainBooksButton->hide();
        ui->maintainBooksLabel->hide();
    }

   this->loggedInUserID = loggedInUserID;
   this->admin = admin;
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
    MaintainUsers *mu = new MaintainUsers(admin, this);
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
    ViewAccount *va = new ViewAccount(admin, loggedInUserID, this);
    va->show();
}

