#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QDialog>
#include "login.h"

namespace Ui {
class mainscreen;
}

class mainscreen : public QDialog
{
    Q_OBJECT

public:

    explicit mainscreen(QString, int, int, login *parent = nullptr);
    ~mainscreen();

    int admin, user_id;
    QString user, username;

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

#endif // MAINSCREEN_H
