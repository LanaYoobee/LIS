#pragma once

#include <QDialog>
#include "login.h"
#include "createaccount.h"
#include "viewaccount.h"

namespace Ui {
class MaintainUsers;
}

class MaintainUsers : public QDialog
{
    Q_OBJECT

public:
    explicit MaintainUsers(int, login *parent = nullptr);
    ~MaintainUsers();

    int admin;

    login *parent;

private slots:
    void on_quitButton_clicked();

    void on_addUserButton_clicked();

    void on_userSearch_returnPressed();

private:
    Ui::MaintainUsers *ui;
};
