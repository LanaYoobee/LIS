#include "browse.h"
#include "ui_browse.h"
#include "db_connect.h"

browse::browse(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::browse)
{
    ui->setupUi(this);


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


void browse::on_pushButton_clicked()
{
    db_connect db;

    //set up variables needed for authentication
    QSqlQuery qry;
    QString title, image_small;

    //prepare the query. select 30 books at random.

    qry.prepare("select title, image_small from books order by random() limit 1");
    qry.exec();


    if(qry.next()) //check if there were any results for this username
    {

        title = qry.value(0).toString(); //title of the book from the db
        image_small = qry.value(1).toString(); //the URl from the db

//for debugging purposes
        ui->plainTextEdit->setTextInteractionFlags(Qt::TextSelectableByMouse);
        ui->plainTextEdit->setPlainText(title);

        QNetworkAccessManager *networkAccessManager = new QNetworkAccessManager;

        QNetworkRequest request(image_small);

        QNetworkReply *reply = networkAccessManager->get(request);

        QEventLoop loop;
        connect(reply,SIGNAL(finished()),&loop,SLOT(quit()));
        loop.exec();

        QByteArray bytes = reply->readAll();
        QImage img(64, 64, QImage::Format_RGB32);
        img.loadFromData(bytes);

        ui->bookImage_10->setPixmap(QPixmap::fromImage(img).scaledToHeight(64));
        ui->bookNameLabel_10->setText(title);
    }

    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);





    //can't figure out how to loop through all buttons

//    for (int i = 1; i <=30; i++)
//    {
//        labels.append(new QLable(Qstring:number(30-i)));

//       // QLineEdit *edit = ui->findChild<QLineEdit *>(name_template.arg(i));
//      //  answers += edit->text();
//       // ui->("bookImage_"+i)->
//    }

//    for(int i=0; i<=30; i++)
//    {
//        ui->bookImage_10>setPixmap(QPixmap::fromImage(img).scaledToHeight(64));
//    }
}

