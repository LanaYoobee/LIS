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

    ui->confirmLabel->hide();

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

    QSqlQuery qry;
    qry.prepare("select book_id, username from borrowing where book_id = :book_id");
    qry.bindValue(":book_id", book_id);
    qry.exec();
    QString borrowed_user;

    if(qry.next())
    {
        borrowed_user = qry.value(1).toString();
    }
    else borrowed_user.isEmpty();

    qDebug() << "admin status: " +admin;

    qDebug() << "borrowed user: " +borrowed_user;
    qDebug() << "logged in user: " +loggedInUser;

    //if the book is available, we can borrow it, otherwise we can only reserve it
    if (due_date > QDate::currentDate() )
    {
        ui->borrowBookButton->hide();
        ui->borrowBookLabel->hide();

        //if the logged in user is the same user whose books we're looking at, then we can return the book on their behalf. or they can return it themselves.

        if (loggedInUser == borrowed_user || admin == 1)
        {
            ui->returnBookButton->show();
            ui->returnBookLabel->show();
            ui->reserveBookButton->hide();
            ui->reserveBookLabel->hide();
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
    //set up variables needed for borrowing the book
    QSqlQuery qry;
    QDate date_borrowed = QDate::currentDate();
    QString loggedInUser = parent->getUsername();

    QDate due_date = date_borrowed.addDays(20);
    QString reserved_user;
    qDebug() << "Book ID "+book_id;

    qry.prepare("select user_reserved from borrowing where book_id=:book_id");
    qry.bindValue(":book_id", book_id);
    qry.exec();
    if(qry.next())
    {

        reserved_user = qry.value(0).toString();
    }
    else reserved_user.isEmpty();

    qDebug() <<"Reserved: " +reserved_user;
    qDebug() <<"Logged in: " +loggedInUser;

    if (reserved_user != loggedInUser && !reserved_user.isEmpty())
    {
        QMessageBox::critical(this, "LIS", "Book is reserved by another person");
    }
    else
    {

        qry.prepare("INSERT INTO borrowing(book_id, username, date_borrowed, due_date) VALUES(:book_id, :loggedInUser,  :date_borrowed, :due_date);");
        qry.bindValue(":book_id", book_id);
        qry.bindValue(":loggedInUser", loggedInUser);
        qry.bindValue(":date_borrowed", date_borrowed);
        qry.bindValue(":due_date", due_date);


        if(qry.exec())
        {
            ui->confirmLabel->show();
            ui->confirmLabel->setText("Book borrowed, due date is "+due_date.toString("dd MMM yyyy"));
        }
    }
}


void BookDetails::on_returnBookButton_clicked()
{

    //set up variables needed for borrowing the book
    QSqlQuery qry;
    QDate date_returned = QDate::currentDate();

    qry.prepare("update borrowing set date_returned = :date_returned where book_id= :book_id");
    qry.bindValue(":book_id", book_id);
    qry.bindValue(":date_returned", date_returned);

    if(qry.exec())
    {
        ui->confirmLabel->show();
        ui->confirmLabel->setText("Book returned");
    }

}


void BookDetails::on_reserveBookButton_clicked()
{

    //set up variables needed for reserving the book
    QSqlQuery qry;
    QString loggedInUser = parent->getUsername();

    qry.prepare("update borrowing set user_reserved=:user_reserved where book_id = :book_id");

    qry.bindValue(":book_id", book_id);
    qry.bindValue(":user_reserved", loggedInUser);


    if(qry.exec())
    {
        ui->confirmLabel->show();
        ui->confirmLabel->setText("Book reserved");
    }
}

