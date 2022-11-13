#ifndef BROWSE_H
#define BROWSE_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QMessageBox>

namespace Ui {
class browse;
}

class browse : public QDialog
{
    Q_OBJECT

public:
    explicit browse(QString callType, QWidget *parent = nullptr);
    ~browse();

private slots:
    void on_quitButton_clicked();

    void randomBooks();

    void displayBooks();

    //QImage img, QString title
    void showBookDetails(QImage img, QString title);

private:
    Ui::browse *ui;
};

#endif // BROWSE_H
