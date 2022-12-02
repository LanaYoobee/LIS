//#ifndef SEARCHBOOKS_H
//#define SEARCHBOOKS_H

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
    explicit SearchBooks(QWidget *parent = nullptr);
    ~SearchBooks();

private slots:
    void on_quitButton_clicked();

    void on_searchTitleButton_clicked();

    void on_searchAuthorButton_clicked();

private:
    Ui::SearchBooks *ui;
};

//#endif // SEARCHBOOKS_H
