#include "browse.h"
#include "ui_browse.h"


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
    this->hide();
}


void browse::on_pushButton_clicked()
{
    QNetworkAccessManager *nam = new QNetworkAccessManager;

    QNetworkRequest request(QUrl("https://images.unsplash.com/photo-1579353977828-2a4eab540b9a?ixlib=rb-4.0.3&ixid=MnwxMjA3fDB8MHxwaG90by1wYWdlfHx8fGVufDB8fHx8&auto=format&fit=crop&w=1074&q=80"));

    QNetworkReply *reply = nam->get(request);

    QEventLoop loop;
    QObject::connect(reply,SIGNAL(finished()),&loop,SLOT(quit()));
    loop.exec();

    QByteArray bytes = reply->readAll();
    QImage img(20, 20, QImage::Format_Indexed8);
    img.loadFromData(bytes);

    ui->bookImage->setPixmap(QPixmap::fromImage(img).scaledToHeight(64));
}

