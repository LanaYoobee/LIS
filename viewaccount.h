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
    explicit ViewAccount(int, QString, login *parent = nullptr);
    ~ViewAccount();

    QString searchedUsername;

    login *parent;

private slots:
    void on_quitButton_clicked();

    void on_deleteUserButton_clicked();

    void showBookDetails(int, QImage, QString, QString, QDate);

    void on_saveAccountButton_clicked();

private:
    Ui::ViewAccount *ui;
};

