#include "viewaccount.h"
#include "ui_viewaccount.h"

ViewAccount::ViewAccount(int admin, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewAccount)
{
    ui->setupUi(this);

    //if the user is not an admin, hide admin function buttons
    if (admin == 0)
    {
        ui->deleteUserButton->hide();
        ui->deleteUserLabel->hide();
    }
}

ViewAccount::~ViewAccount()
{
    delete ui;
}

void ViewAccount::on_quitButton_clicked()
{
     this->close();
}


void ViewAccount::on_deleteUserButton_clicked()
{

}

