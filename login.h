
#pragma once

#include <QMainWindow>
#include <QMessageBox>
#include <QtSql>

QT_BEGIN_NAMESPACE
namespace Ui { class login; }
QT_END_NAMESPACE



class login : public QMainWindow
{
    Q_OBJECT


public:
    login(QWidget *parent = nullptr);
    ~login();

    QString getUsername();
    int getAdmin();


private slots:
    void on_passwordEntry_returnPressed();


private:
    Ui::login *ui;
    QString loggedInUser;
    int admin;
    void setUsername(QString);
    void setAdmin(int);

};
