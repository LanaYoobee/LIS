#ifndef VIEWACCOUNT_H
#define VIEWACCOUNT_H

#include <QDialog>
#include "login.h"
#include "browse.h"
#include "bookdetails.h"
#include "mainscreen.h"

namespace Ui {
class ViewAccount;
}

class ViewAccount : public QDialog
{
    Q_OBJECT

public:
    explicit ViewAccount(int, int, QWidget *parent = nullptr);
    ~ViewAccount();

private slots:
    void on_quitButton_clicked();

    void on_deleteUserButton_clicked();

    void showBookDetails(QImage, QString, QString, QDate);

    QImage imageFromUrl(QString);

private:
    Ui::ViewAccount *ui;
};

#endif // VIEWACCOUNT_H
