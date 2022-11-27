#ifndef BROWSE_H
#define BROWSE_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QMessageBox>
#include "login.h"

namespace Ui {
class browse;
}

class browse : public QDialog
{
    Q_OBJECT

public:
    explicit browse(QString, QString, QWidget *parent = nullptr);
    ~browse();

private slots:
    void on_quitButton_clicked();

    void displayBooks(QSqlQuery, int);

    void showBookDetails(QImage, QString, QString, QDate);

    QImage imageFromUrl(QString);

private:
    Ui::browse *ui;
};

#endif // BROWSE_H
