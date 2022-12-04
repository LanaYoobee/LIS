#include "viewaccount.h"
#include "ui_viewaccount.h"


ViewAccount::ViewAccount(int admin, QString searchedUsername, login *parent) :
    QDialog(parent),
    ui(new Ui::ViewAccount)
{
    ui->setupUi(this);

    this->parent = parent;

    ui->confirmLabel->hide();

    this->searchedUsername = searchedUsername;

    //we don't want non-admins deleting users and we don't want the main admin deleting itself
    if (admin != 1 || searchedUsername == "admin")
    {
        ui->deleteUserButton->hide();
        ui->deleteUserLabel->hide();
    }

    //prepare the query.
    QSqlQuery qry;
    qry.prepare("select first_name, surname, phone, title, image_small, image_large, author, users.username, books.id, due_date from users left join borrowing on borrowing.username = users.username left join books on borrowing.book_id = books.ID where users.username = :searchedUsername order by random()");
    qry.bindValue(":searchedUsername", searchedUsername);
    qry.exec();

    QString title, image_small, image_large, author;
    QImage img_thumb, img_full;
    QDate due_date, date_returned;
    int book_id, borrowed_books;

    if(qry.first())
    {
        ui->firstNameLineEdit->setText(qry.value(0).toString());
        ui->surnameLineEdit->setText(qry.value(1).toString());
        ui->phoneLineEdit->setText(qry.value(2).toString());
    }

    qry.prepare("select count(*) from borrowing where borrowing.username = :searchedUsername");
    qry.bindValue(":searchedUsername", searchedUsername);
    qry.exec();

    if(qry.first())
    {
        borrowed_books = qry.value(0).toInt();
    }

    if (borrowed_books != 0)
    {

    //we only show five borrowed books

    for(int i=1; i<=5; i++)
    {
        if(qry.next())
        {

            title = qry.value(3).toString(); //title of the book from the db
            image_small = qry.value(4).toString(); //the URl of the thumbnail image from the db
            image_large = qry.value(5).toString(); //the URl of the large image from the db
            author = qry.value(6).toString(); //author of the book from the db
            book_id = qry.value(8).toInt(); //book id
            due_date = QDate::fromString(qry.value(9).toString(),"yyyy-MM-dd"); //date borrowed
            date_returned = QDate::fromString(qry.value(10).toString(),"yyyy-MM-dd"); //date borrowed

            if (due_date.isNull() || (!due_date.isNull() && !date_returned.isNull()))
                due_date = QDate::currentDate();


            img_thumb = imageFromUrl(image_small);
            img_full = imageFromUrl(image_large);


            QPushButton *bookButton = new QPushButton(this);
            //            QLabel *bookLabel = new QLabel();

            bookButton->setMinimumSize(64,64);
            bookButton->setMaximumSize(64,64);
            bookButton->setIconSize(QSize(64,64));
            QIcon buttonIcon(QPixmap::fromImage(img_thumb));
            bookButton->setIcon(buttonIcon);

            //TODO wanted to show labels as well but they don't line up properly, think need a combination of vertical box and gridlayout but can't figure it out


            //            bookLabel->setWordWrap(1);
            //            bookLabel->setText(title);

            //            QVBoxLayout *verticalBox = new QVBoxLayout(this);

            //            verticalBox->addWidget(bookButton);
            //            verticalBox->addWidget(bookLabel);

            //            ui->gridLayout->addLayout(verticalBox, j, i);

            ui->horizontalLayout->addWidget(bookButton, i);
            //            ui->gridLayout->addWidget(bookLabel, j, i);

            //this code allows us to interact with dynamically generated buttons and pass the parameters to the next screen
            connect(bookButton, &QPushButton::clicked, [=](){showBookDetails(book_id, img_full, title, author, due_date);});

        }
    }
    }

}

ViewAccount::~ViewAccount()
{
    delete ui;
}

void ViewAccount::on_quitButton_clicked()
{
    this->close();
}


void ViewAccount::on_deleteUserButton_clicked()
{
    QSqlQuery qry;
    qry.prepare("delete from users where username = :searchedUsername");
    qry.bindValue(":searchedUsername", searchedUsername);
    qry.exec();

    if(qry.exec()) //check if there were any results for this username
    {
        ui->confirmLabel->show();
        ui->confirmLabel->setText("User Deleted");
    }
}


//open the screen with details of one book
void ViewAccount::showBookDetails(int book_id, QImage img_full, QString title, QString author, QDate due_date)
{
    BookDetails *bd = new BookDetails(book_id, img_full, title, author, due_date, parent); //pass thef full image and the title to the other screen
    bd->show(); //show the details of the book window
}

void ViewAccount::on_saveAccountButton_clicked()
{
    int updatedPhone;
    QString updatedFirstName, updatedSurname, updatedPassword;

    updatedFirstName = ui->firstNameLineEdit->text();
    updatedSurname = ui->surnameLineEdit->text();
    updatedPhone = ui->phoneLineEdit->text().toInt();
    updatedPassword = ui->passwordLineEdit->text();

    QSqlQuery qry;


    if (!updatedPassword.isEmpty())
    {
        QString salt = QtBCrypt::generateSalt();
        QString hashedPassword = QtBCrypt::hashPassword(updatedPassword, salt);
        qry.prepare("update users set phone = :updatedPhone, first_name = :updatedFirstName, surname = :updatedSurname, password = :hashedPassword where username = :searchedUsername");
        qry.bindValue(":searchedUsername", searchedUsername);
        qry.bindValue(":hashedPassword", hashedPassword);
        qry.bindValue(":updatedFirstName", updatedFirstName);
        qry.bindValue(":updatedSurname", updatedSurname);
        qry.bindValue(":updatedPhone", updatedPhone);

    }
    else
    {
        qry.prepare("update users set phone = :updatedPhone, first_name = :updatedFirstName, surname = :updatedSurname where username = :searchedUsername");
        qry.bindValue(":searchedUsername", searchedUsername);
        qry.bindValue(":updatedFirstName", updatedFirstName);
        qry.bindValue(":updatedSurname", updatedSurname);
        qry.bindValue(":updatedPhone", updatedPhone);
    }

    if(qry.exec()) //check if query executed
    {
        ui->confirmLabel->show();
        ui->confirmLabel->setText("User Updated");
    }
}

