#include "maintainusers.h"
#include "ui_maintainusers.h"
#include "createaccount.h"

MaintainUsers::MaintainUsers(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MaintainUsers)
{
    ui->setupUi(this);
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


}

