#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QMessageBox>
#include "db_connect.h"
#include "db_close.h"

QT_BEGIN_NAMESPACE
namespace Ui { class login; }
QT_END_NAMESPACE



class login : public QMainWindow
{
    Q_OBJECT


public:
    login(QWidget *parent = nullptr);
    ~login();

private slots:
    void on_passwordEntry_returnPressed();

    void on_pushButton_clicked();

    void on_login_destroyed();

private:
    Ui::login *ui;

};
#endif // LOGIN_H
