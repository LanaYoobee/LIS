#include "browse.h"
#include "ui_browse.h"
#include "bookdetails.h"

browse::browse(QString callType, QString search, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::browse)
{
    ui->setupUi(this);

    ui->welcomeLabel_3->hide();
    if (callType == "searchTitle")
    {
        this->show();
        //prepare the query.
        QSqlQuery qry, qryCounter;
        int qryCount;
        qry.prepare("select title, image_small, image_large, author from books where title like :title order by random()");
        qry.bindValue(":title", search);

        //we're doing a second count query because QSqlQuery.size() is not supported in sqlite
        //we need the count query to control the loop of buttons in displayBooks

        qryCounter.prepare("select count(*) from books where title like :title");
        qryCounter.bindValue(":title", search);
        qryCounter.exec();

        if(qryCounter.next())
        {
            qryCount = qryCounter.value(0).toInt();
        }
        qry.exec();
        displayBooks(std::move(qry), qryCount);
    }

    else
    if (callType == "searchAuthor")
    {
        this->show();
        //prepare the query.
        QSqlQuery qry, qryCounter;
        int qryCount;
        qry.prepare("select title, image_small, image_large, author from books where author like :author order by random()");
        qry.bindValue(":author", search);

        //we're doing a second count query because QSqlQuery.size() is not supported in sqlite
        //we need the count query to control the loop of buttons in displayBooks

        qryCounter.prepare("select count(*) from books where author like :author");
        qryCounter.bindValue(":author", search);
        qryCounter.exec();

        if(qryCounter.next())
        {
            qryCount = qryCounter.value(0).toInt();
        }
        qry.exec();
        displayBooks(std::move(qry), qryCount);
    }

    else
    if (callType == "browse")
    {
        this->show(); //we show the screen first because sqlite query is slow and otherwise the user may think nothing is happening if the screen does not come up when query is executing
        ui->welcomeLabel->hide();
        ui->welcomeLabel_3->show();
        ui->welcomeLabel_3->setText("Random selection of 30 books");
        //prepare the query. select 30 books at random.
         db_connect();
        QSqlQuery qry;
        qry.prepare("select title, image_small, image_large, author from books order by random() limit 30");
        qry.exec();
        displayBooks(std::move(qry), 30);
        QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
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


//reusable class to display books from a given query
void browse::displayBooks(QSqlQuery qry, int size)

{


    QString title, image_small, image_large, author;
    QImage img_thumb, img_full;

    //if there are 10 or fewer books, show one row

    if (size<=10)
    {
        ui->welcomeLabel->setText("There were "+QString("%1").arg(size)+" books found.");
        for(int i=1; i<=size; i++)
        {
            if(qry.next())
            {
                title = qry.value(0).toString(); //title of the book from the db
                image_small = qry.value(1).toString(); //the URl of the thumbnail image from the db
                image_large = qry.value(2).toString(); //the URl of the large image from the db
                author = qry.value(3).toString(); //author of the book from the db
            }

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

            ui->gridLayout->addWidget(bookButton, 1, i);
            //            ui->gridLayout->addWidget(bookLabel, j, i);

            //this code allows us to interact with dynamically generated buttons and pass the parameters to the next screen
            connect(bookButton, &QPushButton::clicked, [=](){showBookDetails(img_full, title, author);});

        }
    }
    else
        //if there are 11-29 results then we want to show them in blocks of 10

        if (size>10 && size<30){

            int divide = size / 10;
            int remainder = size % 10;

             ui->welcomeLabel->setText("There were "+QString("%1").arg(size)+" books found.");
            for(int i=1; i<=10; i++)
            {
                for (int j =1; j<=divide; j++)
                {
                    //sqlite query is very slow
                    if(qry.next())
                    {
                        title = qry.value(0).toString(); //title of the book from the db
                        image_small = qry.value(1).toString(); //the URl of the thumbnail image from the db
                        image_large = qry.value(2).toString(); //the URl of the large image from the db
                        author = qry.value(3).toString(); //author of the book from the db
                    }

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

                    ui->gridLayout->addWidget(bookButton, j, i);
                    //            ui->gridLayout->addWidget(bookLabel, j, i);

                    //this code allows us to interact with dynamically generated buttons and pass the parameters to the next screen
                    connect(bookButton, &QPushButton::clicked, [=](){showBookDetails(img_full, title, author);});

                }
            }

            //remainder of buttons if the number of results is not divisible by 10

            for(int i = 1; i <= remainder; i++) {
                if(qry.next())
                {
                    title = qry.value(0).toString(); //title of the book from the db
                    image_small = qry.value(1).toString(); //the URl of the thumbnail image from the db
                    image_large = qry.value(2).toString(); //the URl of the large image from the db
                    author = qry.value(3).toString(); //author of the book from the db
                }

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


                int j = (divide == 2) ? 3 : 2;

                ui->gridLayout->addWidget(bookButton, j, i);
                //            ui->gridLayout->addWidget(bookLabel, j, i);

                //this code allows us to interact with dynamically generated buttons and pass the parameters to the next screen
                connect(bookButton, &QPushButton::clicked, [=](){showBookDetails(img_full, title, author);});
            }
        }

        else
        {
            //if there 30 or more results, we show only 30


             ui->welcomeLabel->setText("There were "+QString("%1").arg(size)+" books found. Displaying random 30.");
            for(int i=1; i<=10; i++)
            {
                for (int j =1; j<=3; j++)
                {

                    //sqlite query is very slow
                    if(qry.next())
                    {
                        title = qry.value(0).toString(); //title of the book from the db
                        image_small = qry.value(1).toString(); //the URl of the thumbnail image from the db
                        image_large = qry.value(2).toString(); //the URl of the large image from the db
                        author = qry.value(3).toString(); //author of the book from the db
                    }

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

                    ui->gridLayout->addWidget(bookButton, j, i);
                    //            ui->gridLayout->addWidget(bookLabel, j, i);

                    //this code allows us to interact with dynamically generated buttons and pass the parameters to the next screen
                    connect(bookButton, &QPushButton::clicked, [=](){showBookDetails(img_full, title, author);});

                }
            }
        }
}


//open the screen with details of one book
void browse::showBookDetails(QImage img_full, QString title, QString author)
{
    BookDetails *bd = new BookDetails(img_full, title, author, this); //pass thef full image and the title to the other screen
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
