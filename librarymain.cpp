#include "librarymain.h"
#include "ui_librarymain.h"

librarymain::librarymain(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::librarymain)
{
    ui->setupUi(this);
}

librarymain::~librarymain()
{
    delete ui;
}

void librarymain::on_returnButton_clicked()
{
    QApplication::quit();
}

