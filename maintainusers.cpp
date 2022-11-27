#include "maintainusers.h"
#include "ui_maintainusers.h"
#include "createaccount.h"
#include "viewaccount.h"

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
    int user_id = ui->userSearch->text().toInt();


    ViewAccount *va = new ViewAccount(user_id, this);
    va->show();

}

