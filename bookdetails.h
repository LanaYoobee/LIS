#ifndef BOOKDETAILS_H
#define BOOKDETAILS_H

#include <QDialog>
#include "login.h"

namespace Ui {
class BookDetails;
}

class BookDetails : public QDialog
{
    Q_OBJECT

    //QImage img, QString title,
public:
    explicit BookDetails(QImage, QString, QString, QDate, QWidget *parent = nullptr);
    ~BookDetails();

private slots:
    void on_quitButton_clicked();

    void on_borrowBookButton_clicked();

private:
    Ui::BookDetails *ui;
};

#endif // BOOKDETAILS_H
