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
    ui->confirmLabel_2->hide();

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
    //set up variables needed for borrowing the book
    QSqlQuery qry;
    QDate date_borrowed = QDate::currentDate();
    QString loggedInUser = parent->getUsername();

    QDate due_date = date_borrowed.addDays(20);

    qry.prepare("INSERT INTO borrowing(book_id, username, date_borrowed, due_date) VALUES(:book_id, :loggedInUser,  :date_borrowed, :due_date);");

    qry.bindValue(":book_id", book_id);
     qry.bindValue(":loggedInUser", loggedInUser);
    qry.bindValue(":date_borrowed", date_borrowed);
    qry.bindValue(":due_date", due_date);


    if(qry.exec())
    {
        ui->confirmLabel_2->show();
        ui->confirmLabel_2->setText("Book borrowed, due date is "+due_date.toString("dd MMM yyyy"));
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
        }

}


void BookDetails::on_reserveBookButton_clicked()
{

}

