#include "bookdetails.h"
#include "ui_bookdetails.h"

//QImage img, QString title,
BookDetails::BookDetails(QImage img, QString title, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BookDetails)
{
    ui->setupUi(this);

    ui->bookImage->setPixmap(QPixmap::fromImage(img).scaledToHeight(268));
    ui->titleEdit->setText(title);
    ui->titleEdit->home(1);
}

BookDetails::~BookDetails()
{
    delete ui;
}

//close the window when quit button is clicked
void BookDetails::on_quitButton_clicked()
{
    this->close();
}

