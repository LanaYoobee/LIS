#include "bookdetails.h"
#include "ui_bookdetails.h"

//QImage img, QString title,
BookDetails::BookDetails(QImage img, QString title, QString author, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BookDetails)
{
    ui->setupUi(this);

    ui->bookImage->setPixmap(QPixmap::fromImage(img).scaledToHeight(268));
    ui->titleEdit->setText(title);
    ui->titleEdit->home(1); //display the cursor at the start of the line
    ui->authorEdit->setText(author);
    ui->authorEdit->home(1); //display the cursor at the start of the line
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

