#include "bookdetails.h"
#include "ui_bookdetails.h"
#include "login.h"

BookDetails::BookDetails(int book_id, QImage img, QString title, QString author, QDate due_date, login *parent) :
    QDialog(parent),
    ui(new Ui::BookDetails)
{
    ui->setupUi(this);

    this->parent = parent;
    this->book_id = book_id;

    qDebug() << "book id when we enter view" << book_id;
    qDebug() << "book id in class " << this->book_id;

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

    if (admin != 1)
    {
        ui->deleteBookButton->hide();
        ui->deleteBookLabel->hide();
        ui->updateBookLabel->hide();
        ui->updateBookButton->hide();
    }

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

    qDebug() << "admin status: " << admin;

    qDebug() << "borrowed user: " << borrowed_user;
    qDebug() << "logged in user: " << loggedInUser;

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

        qry.finish();

}


void BookDetails::on_returnBookButton_clicked()
{

    //set up variables needed for returning the book
    QSqlQuery qry;

    qry.prepare("delete from borrowing where book_id= :book_id");
    qry.bindValue(":book_id", book_id);

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


void BookDetails::on_deleteBookButton_clicked()
{
    //set up variables needed for deleting the book
    QSqlQuery qry;
    int borrowed_books;

    qry.prepare("select count(*) from borrowing where book_id = :book_id");
    qry.bindValue(":book_id", book_id);
    qry.exec();

    if(qry.first())
    {
        borrowed_books = qry.value(0).toInt();
    }

    //only books that are currently not checked out are allowed to be deleted.

    if (borrowed_books != 0)
        QMessageBox::critical(this, "LIS", "Books is currently checked out, please return it first");

    else
    {
        qry.prepare("delete from books where id = :book_id");
        qry.bindValue(":book_id", book_id);

        if(qry.exec())
        {
            ui->confirmLabel->show();
            ui->confirmLabel->setText("Book deleted");
        }
    }
}


void BookDetails::on_updateBookButton_clicked()
{
    QString updatedTitle, updatedAuthor;

    updatedTitle = ui->titleEdit->text();
    updatedAuthor = ui->authorEdit->text();

    qDebug() << "title " << updatedTitle;
    qDebug() << "author " << updatedAuthor;
    qDebug() << "book id " << book_id;

    QSqlQuery qry;

    qry.prepare("update books set title = :updatedTitle, author = :updatedAuthor where id = :book_id");
    qry.bindValue(":updatedTitle", updatedTitle);
    qry.bindValue(":updatedAuthor", updatedAuthor);
    qry.bindValue(":book_id", book_id);

    if(qry.exec()) //check if query executed
    {
        ui->confirmLabel->show();
        ui->confirmLabel->setText("Book Updated");
    }
}
