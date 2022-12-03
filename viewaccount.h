//#ifndef VIEWACCOUNT_H
//#define VIEWACCOUNT_H

#pragma once

#include <QDialog>
#include "login.h"
#include "browse.h"
#include "bookdetails.h"
#include "mainscreen.h"
#include "qtbcrypt.h"

namespace Ui {
class ViewAccount;
}

class ViewAccount : public QDialog
{
    Q_OBJECT

public:
    explicit ViewAccount(int, QString, QWidget *parent = nullptr);
    ~ViewAccount();

    QString searchedUsername;

private slots:
    void on_quitButton_clicked();

    void on_deleteUserButton_clicked();

    void showBookDetails(QImage, QString, QString, QDate, QString);

    void on_saveAccountButton_clicked();

private:
    Ui::ViewAccount *ui;
};

//#endif // VIEWACCOUNT_H
