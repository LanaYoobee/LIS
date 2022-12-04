#include "searchbooks.h"
#include "ui_searchbooks.h"
#include "createbook.h"
#include "browse.h"

SearchBooks::SearchBooks(login *parent) :
    QDialog(parent),
    ui(new Ui::SearchBooks)
{
    ui->setupUi(this);
    this->parent = parent;
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

    QString enteredTitle;

    enteredTitle = ui->titleSearchLineEdit->text(); //get text from the search screen
    enteredTitle = QString("%%1%").arg(enteredTitle);

    browse *b = new browse("searchTitle", enteredTitle, parent);
    b->show();

}


void SearchBooks::on_searchAuthorButton_clicked()
{

    QString enteredAuthor;

    enteredAuthor = ui->authorSearchLineEdit->text(); //get text from the search screen
    enteredAuthor = QString("%%1%").arg(enteredAuthor);

    browse *b = new browse("searchAuthor", enteredAuthor, parent);
    b->show();

}


void SearchBooks::on_addBookButton_clicked()
{
    CreateBook *cb = new CreateBook(this);
    cb->show();
}
