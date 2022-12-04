
#pragma once

#include <QDialog>

#include <QMessageBox>
#include "login.h"
#include "imagefromurl.h"


namespace Ui {
class browse;
}

class browse : public QDialog
{
    Q_OBJECT

public:
    explicit browse(QString, QString, login *parent = nullptr);
    ~browse();

    login *parent;

private slots:
    void on_quitButton_clicked();

    void displayBooks(QSqlQuery, int);

    void showBookDetails(int, QImage, QString, QString, QDate);

private:
    Ui::browse *ui;
};

