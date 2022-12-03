#include "bookdetails.h"
#include "ui_bookdetails.h"
#include "login.h"

BookDetails::BookDetails(int book_id, QImage img, QString title, QString author, QDate due_date, QString searchedUsername, login *parent) :
    QDialog(parent),
    ui(new Ui::BookDetails)
{
    ui->setupUi(this);

    this->parent = parent;
    this->book_id = book_id;

    ui->bookImage->setPixmap(QPixmap::fromImage(img).scaledToHeight(268));
    ui->titleEdit->setText(title);
    ui->titleEdit->home(1); //display the cursor at the start of the line
    ui->authorEdit->setText(author);
    ui->authorEdit->home(1); //display the cursor at the start of the line
    ui->dateEdit->setDate(due_date);
    ui->returnBookButton->hide();
    ui->returnBookLabel->hide();

    QString loggedInUser = parent->getUsername();
    int admin = parent->getAdmin();

    qDebug() << "admin status: " +admin;

    //if the logged in user is the same user whose books we're looking at, then we can return the book



        //if the book is available, we can borrow it, otherwise we can only reserve it
        if (due_date > QDate::currentDate())
        {
            ui->borrowBookButton->hide();
            ui->borrowBookLabel->hide();

            if (loggedInUser == searchedUsername || admin == 1)
            {
                ui->returnBookButton->show();
                ui->returnBookLabel->show();
            }
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


void BookDetails::on_returnBookButton_clicked()
{

        //set up variables needed for borrowing the book
        QSqlQuery qry;
        QDate date_returned = QDate::currentDate();

        qry.prepare("update borrowing set date_returned = :date_returned where book_id= :book_id");
        qry.bindValue(":book_id", book_id);
        qry.bindValue(":date_returned", date_returned);
        qry.exec();

        if(qry.exec())
        {
            QMessageBox::critical(this, "LIS", "Book returned");
        }

}


void BookDetails::on_reserveBookButton_clicked()
{

}

