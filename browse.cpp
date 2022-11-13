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
    this->show();
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
    QSqlQuery qry;

    //prepare the query. select 30 books at random.
    qry.prepare("select title, image_small, image_large from books order by random() limit 30");
    qry.exec();


    QString title, image_small, image_large;
    QImage img_thumb, img_full;

    for(int i=1; i<=30; i++)
    {
        for (int j =1; j<=3; j++)
        {

           if(qry.next())
            {
                title = qry.value(0).toString(); //title of the book from the db
                image_small = qry.value(1).toString(); //the URl from the db
                image_large = qry.value(2).toString(); //the URl from the db
            }

           img_thumb = imageFromUrl(image_small);
           img_full = imageFromUrl(image_large);

            QPushButton *bookButton = new QPushButton(this);
            QLabel *bookLabel = new QLabel();

            bookButton->setMinimumSize(64,64);
            bookButton->setMaximumSize(64,64);
            bookButton->setIconSize(QSize(64,64));
            QIcon buttonIcon(QPixmap::fromImage(img_thumb));
            bookButton->setIcon(buttonIcon);

            bookLabel->setWordWrap(1);
            bookLabel->setText(title);

          //  QVBoxLayout *verticalBox = new QVBoxLayout(this);

//            verticalBox->addWidget(bookButton);
//            verticalBox->addWidget(bookLabel);

//            ui->gridLayout->addLayout(verticalBox, j, i);

            ui->gridLayout->addWidget(bookButton, j, i);
//            ui->gridLayout->addWidget(bookLabel, j, i);

            connect(bookButton, &QPushButton::clicked, [=](){showBookDetails(img_full, title);});
        }
    }
}

//open the screen with details of one book
void browse::showBookDetails(QImage img_full, QString title)
{
    BookDetails *bd = new BookDetails(img_full, title, this); //pass thef full image and the title to the other screen
    bd->show(); //show the details of the book window
}


//reusable class for getting the images from URLs stored in the database
QImage browse::imageFromUrl(QString url)
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
