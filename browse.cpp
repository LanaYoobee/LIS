#include "browse.h"
#include "ui_browse.h"
#include "db_connect.h"
#include "bookdetails.h"

browse::browse(QString callType, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::browse)
{
    ui->setupUi(this);

if (callType == "search")
{
    //do something
}
else if (callType == "browse")
{
    randomBooks();
}
}

browse::~browse()
{
    delete ui;
}



//as this is a secondary screen, we don't need to log out, just close the window
void browse::on_quitButton_clicked()
{
    this->close();
}


void browse::randomBooks()
{
db_connect db;

        ui->welcomeLabel->setText("Random selection of books");

        displayBooks();

    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);

}

void browse::displayBooks()
{
    for(int i=0; i<10; i++)
    {
        for (int j =0; j<3; j++)
        {
            //set up variables needed for authentication
            QSqlQuery qry;
            QString title, image_small, image_large;

            //prepare the query. select 1 book at random.

            qry.prepare("select title, image_small, image_large from books order by random() limit 1");
            qry.exec();

            if(qry.next())
            {
                title = qry.value(0).toString(); //title of the book from the db
                image_small = qry.value(1).toString(); //the URl from the db
                image_large = qry.value(1).toString(); //the URl from the db
            }

            QNetworkAccessManager *networkAccessManager = new QNetworkAccessManager;

            QNetworkRequest request(image_small);

            QNetworkReply *reply = networkAccessManager->get(request);

            QEventLoop loop;
            connect(reply,SIGNAL(finished()),&loop,SLOT(quit()));
            loop.exec();

            QByteArray bytes = reply->readAll();
            QImage img(64, 64, QImage::Format_RGB32);
            img.loadFromData(bytes);

            QPushButton *bookButton = new QPushButton(this);
            QLabel *bookLabel = new QLabel();

            bookButton->setMinimumSize(64,64);
            bookButton->setMaximumSize(64,64);
            bookButton->setIconSize(QSize(64,64));
            QIcon buttonIcon(QPixmap::fromImage(img));
            bookButton->setIcon(buttonIcon);

            bookLabel->setWordWrap(1);
            bookLabel->setText(title);

            ui->gridLayout->addWidget(bookButton, j, i);
//            ui->gridLayout->addWidget(bookLabel, j+1, i);
            connect(bookButton, &QPushButton::clicked, [=](){showBookDetails(img, title);});
        }
    }
}

void browse::showBookDetails(QImage img, QString title)
{//img, title,

    BookDetails *bd = new BookDetails(img, title, this); //pass their first name and the admin status to the main screen window
    bd->show(); //show the main screen window
}

