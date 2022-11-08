#ifndef BROWSE_H
#define BROWSE_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QAuthenticator>
#include <QNetworkReply>
#include <QImageReader>

namespace Ui {
class browse;
}

class browse : public QDialog
{
    Q_OBJECT

public:
    explicit browse(QWidget *parent = nullptr);
    ~browse();

private slots:
    void on_quitButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::browse *ui;
};

#endif // BROWSE_H
