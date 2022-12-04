
#pragma once
#include <QDialog>
#include "login.h"
#include "browse.h"
#include "maintainusers.h"
#include "searchbooks.h"


namespace Ui {
class mainscreen;
}

class mainscreen : public QDialog
{
    Q_OBJECT

public:

    explicit mainscreen(QString, int, QString, login *parent = nullptr);
    ~mainscreen();

    int admin;
    QString userFirstName, loggedInUsername;

    login *parent;

private slots:
    void on_quitButton_clicked();

    void on_maintainUsersButton_clicked();

    void on_maintainBooksButton_clicked();

    void on_browseCatalogueButton_clicked();

    void on_searchBookButton_clicked();

    void on_viewOwnAccountButton_clicked();

private:
    Ui::mainscreen *ui;
};
