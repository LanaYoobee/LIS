#pragma once

#include <QDialog>
#include "login.h"


namespace Ui {
class SearchBooks;
}

class SearchBooks : public QDialog
{
    Q_OBJECT

public:
    explicit SearchBooks(login *parent = nullptr);
    ~SearchBooks();

    login *parent;

private slots:
    void on_quitButton_clicked();

    void on_searchTitleButton_clicked();

    void on_searchAuthorButton_clicked();

    void on_addBookButton_clicked();

private:
    Ui::SearchBooks *ui;
};
