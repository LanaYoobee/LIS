#include "viewaccount.h"
#include "ui_viewaccount.h"
#include "login.h"
#include "browse.h"
#include "bookdetails.h"

ViewAccount::ViewAccount(int user_id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewAccount)
{
    ui->setupUi(this);

    //if the user is not an admin, hide admin function buttons

    //TODO this needs to be logged in user, not the user being passed into thsi function
//    if (login.user_id != 1)
//    {
//        ui->deleteUserButton->hide();
//        ui->deleteUserLabel->hide();
//    }

    //prepare the query.
    QSqlQuery qry;
    qry.prepare("select first_name, surname, phone, title, image_small, image_large, author, users.id, books.id, due_date, date_returned from users left join borrowing on borrowing.user_id = users.ID left join books on borrowing.book_id = books.ID where users.id = :user_id order by random()");
    qry.bindValue(":user_id", user_id);
    qry.exec();

    QString title, image_small, image_large, author;
    QImage img_thumb, img_full;
    QDate due_date, date_returned;

    if(qry.first())
    {

        qDebug() << qry.value(0).toString();
        qDebug() << qry.value(1).toString();
        qDebug() << qry.value(2).toString();

    ui->nameLineEdit->setText(qry.value(0).toString()+" "+qry.value(1).toString());
    ui->phoneLineEdit->setText(qry.value(2).toString());
    }

    qry.exec();

    for(int i=1; i<=5; i++)
    {
    if(qry.next())
    {

//    title = qry.value(0).toString(); //title of the book from the db
//    image_small = qry.value(1).toString(); //the URl of the thumbnail image from the db
//    image_large = qry.value(2).toString(); //the URl of the large image from the db
//    author = qry.value(3).toString(); //author of the book from the db
//    due_date = QDate::fromString(qry.value(6).toString(),"yyyy-MM-dd"); //date borrowed
//    date_returned = QDate::fromString(qry.value(7).toString(),"yyyy-MM-dd"); //date borrowed



        title = qry.value(3).toString(); //title of the book from the db
        image_small = qry.value(4).toString(); //the URl of the thumbnail image from the db
        image_large = qry.value(5).toString(); //the URl of the large image from the db
        author = qry.value(6).toString(); //author of the book from the db
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
      connect(bookButton, &QPushButton::clicked, [=](){showBookDetails(img_full, title, author, due_date);});

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

}

//reusable class for getting the images from URLs stored in the database
QImage ViewAccount::imageFromUrl(QString url)
{
    QNetworkAccessManager *networkAccessManager = new QNetworkAccessManager;

    QNetworkRequest request(url);

    QNetworkReply *reply = networkAccessManager->get(request);

    QEventLoop loop;
    QObject::connect(reply,SIGNAL(finished()),&loop,SLOT(quit()));
    loop.exec();

    QByteArray bytes = reply->readAll();
    QImage img(64, 64, QImage::Format_RGB32);
    img.loadFromData(bytes);

    return img;
}

//open the screen with details of one book
void ViewAccount::showBookDetails(QImage img_full, QString title, QString author, QDate due_date)
{
    BookDetails *bd = new BookDetails(img_full, title, author, due_date, this); //pass thef full image and the title to the other screen
    bd->show(); //show the details of the book window
}