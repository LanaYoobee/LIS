#ifndef ADMINMAIN_H
#define ADMINMAIN_H

#include <QDialog>

namespace Ui {
class adminMain;
}

class adminMain : public QDialog
{
    Q_OBJECT

public:
    explicit adminMain(QString user, QWidget *parent = nullptr);
    ~adminMain();

private slots:
    void on_quitButton_clicked();

private:
    Ui::adminMain *ui;
    QString userFirstName;
};

#endif // ADMINMAIN_H
