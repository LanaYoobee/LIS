#include "searchbooks.h"
#include "ui_searchbooks.h"
#include "browse.h"

SearchBooks::SearchBooks(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchBooks)
{
    ui->setupUi(this);
}

SearchBooks::~SearchBooks()
{
    delete ui;
}

void SearchBooks::on_quitButton_clicked()
{
    this->close();
}


void SearchBooks::on_searchTitleButton_clicked()
{
    db_connect();

    QString enteredTitle;

    enteredTitle = ui->titleSearchLineEdit->text(); //get text from the search screen
    enteredTitle = QString("%%1%").arg(enteredTitle);

    browse *b = new browse("searchTitle", enteredTitle, this);
    b->show();

    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
}


void SearchBooks::on_searchAuthorButton_clicked()
{
    db_connect();

    QString enteredAuthor;

    enteredAuthor = ui->authorSearchLineEdit->text(); //get text from the search screen
    enteredAuthor = QString("%%1%").arg(enteredAuthor);

    browse *b = new browse("searchAuthor", enteredAuthor, this);
    b->show();

    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
}

