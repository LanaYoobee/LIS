#ifndef IMAGEFROMURL_H
#define IMAGEFROMURL_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QImage>
#include <QEventLoop>


class ImageFromURL : public QObject
{
    Q_OBJECT

public:
    ImageFromURL(QString url, QObject *parent = nullptr);
};

#endif // IMAGEFROMURL_H
