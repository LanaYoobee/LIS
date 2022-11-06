#include "membermain.h"
#include "ui_membermain.h"

memberMain::memberMain(QString user, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::memberMain)
{
    userFirstName = user;
    ui->setupUi(this);
    ui->welcomeLabel->setText("Welcome, "+userFirstName);
}

memberMain::~memberMain()
{
    delete ui;
}

