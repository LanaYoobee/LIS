//#ifndef BOOKDETAILS_H

//#define BOOKDETAILS_H

#pragma once

#include <QDialog>
#include "login.h"

namespace Ui {
class BookDetails;
}

class BookDetails : public QDialog
{
    Q_OBJECT

public:
    explicit BookDetails(int, QImage, QString, QString, QDate, login *parent = nullptr);
    ~BookDetails();

    login *parent;
    int book_id;

private slots:
    void on_quitButton_clicked();

    void on_borrowBookButton_clicked();

    void on_returnBookButton_clicked();

    void on_reserveBookButton_clicked();

    void on_deleteBookButton_clicked();

    void on_updateBookButton_clicked();

private:
    Ui::BookDetails *ui;
};

//#endif // BOOKDETAILS_H
