#include "createbook.h"
#include "ui_createbook.h"

CreateBook::CreateBook(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CreateBook)
{
    ui->setupUi(this);
    ui->confirmLabel->hide();
}

CreateBook::~CreateBook()
{
    delete ui;
}

void CreateBook::on_saveAccountButton_clicked()
{
    QString title, author, img_small, img_full;

    title = ui->titleLineEdit->text();
    author = ui->authorLineEdit->text();
    img_small = ui->img_smallLineEdit->text();
    img_full = ui->img_fullLineEdit->text();

    QSqlQuery qry;

        qry.prepare("INSERT INTO books(title, author, image_small, image_large) VALUES(:title, :author, :img_small, :img_full);");
        qry.bindValue(":title", title);
        qry.bindValue(":author", author);
        qry.bindValue(":img_small", img_small);
        qry.bindValue(":img_full", img_full);
        qry.exec();

        ui->confirmLabel->show();
}


void CreateBook::on_quitButton_clicked()
{
    this->close();
}

