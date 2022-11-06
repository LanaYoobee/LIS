#include "adminmain.h"
#include "ui_adminmain.h"

adminMain::adminMain(QString user, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adminMain)
{
    userFirstName = user;
    ui->setupUi(this);
    ui->welcomeLabel->setText("Welcome, "+userFirstName);
}


adminMain::~adminMain()
{
    delete ui;
}

void adminMain::on_quitButton_clicked()
{
    QApplication::quit();

}

