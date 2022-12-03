#include "maintainusers.h"
#include "ui_maintainusers.h"
#include "createaccount.h"
#include "viewaccount.h"

MaintainUsers::MaintainUsers(int admin, login *parent) :
    QDialog(parent),
    ui(new Ui::MaintainUsers)
{
    ui->setupUi(this);
    this->admin = admin;

    this->parent = parent;
}

MaintainUsers::~MaintainUsers()
{
    delete ui;
}

void MaintainUsers::on_quitButton_clicked()
{
    this->close();
}


void MaintainUsers::on_addUserButton_clicked()
{
    CreateAccount *ca = new CreateAccount(this);
    ca->show();
}


void MaintainUsers::on_userSearch_returnPressed()
{
    QString searchedUsername = ui->userSearch->text();


    ViewAccount *va = new ViewAccount(admin, searchedUsername, parent);
    va->show();

}

