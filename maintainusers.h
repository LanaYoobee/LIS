#ifndef MAINTAINUSERS_H
#define MAINTAINUSERS_H

#include <QDialog>

namespace Ui {
class MaintainUsers;
}

class MaintainUsers : public QDialog
{
    Q_OBJECT

public:
    explicit MaintainUsers(QWidget *parent = nullptr);
    ~MaintainUsers();

private slots:
    void on_quitButton_clicked();

    void on_addUserButton_clicked();

    void on_userSearch_returnPressed();

private:
    Ui::MaintainUsers *ui;
};

#endif // MAINTAINUSERS_H
