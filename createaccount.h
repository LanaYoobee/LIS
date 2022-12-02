#pragma once
//#ifndef CREATEACCOUNT_H
//#define CREATEACCOUNT_H

#include <QMainWindow>
#include "login.h"

namespace Ui {
class CreateAccount;
}

class CreateAccount : public QMainWindow
{
    Q_OBJECT

public:
    explicit CreateAccount(QWidget *parent = nullptr);
    ~CreateAccount();

private slots:
    void on_quitButton_clicked();

    void on_saveAccountButton_clicked();

private:
    Ui::CreateAccount *ui;
};

//#endif // CREATEACCOUNT_H
