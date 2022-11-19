#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QDialog>

namespace Ui {
class mainscreen;
}

class mainscreen : public QDialog
{
    Q_OBJECT

public:
    explicit mainscreen(QString, int, QWidget *parent = nullptr);
    ~mainscreen();

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
