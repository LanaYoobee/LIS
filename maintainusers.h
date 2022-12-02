//#ifndef MAINTAINUSERS_H
//#define MAINTAINUSERS_H

#pragma once

#include <QDialog>
#include "login.h"

namespace Ui {
class MaintainUsers;
}

class MaintainUsers : public QDialog
{
    Q_OBJECT

public:
    explicit MaintainUsers(int, QWidget *parent = nullptr);
    ~MaintainUsers();

    int admin;

private slots:
    void on_quitButton_clicked();

    void on_addUserButton_clicked();

    void on_userSearch_returnPressed();

private:
    Ui::MaintainUsers *ui;
};

//#endif // MAINTAINUSERS_H
