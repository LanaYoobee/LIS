#include "imagefromurl.h"

ImageFromURL::ImageFromURL(QString url, QObject *parent)
        : QObject{parent}
{
    QNetworkAccessManager *networkAccessManager = new QNetworkAccessManager;

    QNetworkRequest request(url);

    QNetworkReply *reply = networkAccessManager->get(request);

    QEventLoop loop;
    connect(reply,SIGNAL(finished()),&loop,SLOT(quit()));
    loop.exec();

    QByteArray bytes = reply->readAll();
    QImage img(64, 64, QImage::Format_RGB32);
    img.loadFromData(bytes);

}
