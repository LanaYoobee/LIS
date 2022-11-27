#include "bookdetails.h"
#include "ui_bookdetails.h"
#include "login.h"

BookDetails::BookDetails(QImage img, QString title, QString author, QDate due_date, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BookDetails)
{
    ui->setupUi(this);

    ui->bookImage->setPixmap(QPixmap::fromImage(img).scaledToHeight(268));
    ui->titleEdit->setText(title);
    ui->titleEdit->home(1); //display the cursor at the start of the line
    ui->authorEdit->setText(author);
    ui->authorEdit->home(1); //display the cursor at the start of the line
    ui->dateEdit->setDate(due_date);

    if (due_date > QDate::currentDate())
    {
        ui->borrowBookButton->hide();
        ui->borrowBookLabel->hide();
    }
    else
    {
        ui->reserveBookButton->hide();
        ui->reserveBookLabel->hide();
    }
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


void BookDetails::on_borrowBookButton_clicked()
{
//    //set up variables needed for borrowing the book
//    QSqlQuery qry;
//    QString enteredUser, user, enteredPassword, storedPassword, storedSalt;
//    int admin;

//    qry.prepare("select id from users where username= :username");
//    qry.bindValue(":username", login.user);
//    qry.exec();

//    int user_id = qry.value(0).toInt();

//    //collect user input from the mainwindow
//    enteredUser = ui->usernameEntry->text();
//    enteredPassword = ui->passwordEntry->text();

//    //ui->centralwidget->releaseKeyboard();
//    //prepare the query. bindValue is used to guard against sql injections

//    qry.prepare("select username, password, admin, first_name from users where username= :username");
//    qry.bindValue(":username", login.user);
//    qry.exec();
//    insert into borrowing (book_id, user_id, date_borrowed, due_date, date_returned)
//    select books.id,
//    users.id,
//    CURRENT_DATE,
//    date(CURRENT_DATE,'20 days'),
//    NULL

//    from books, users
//    where title like '%silkie%' and username = 'admin'
}

